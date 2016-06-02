#include "renderer.h"
#include "bitmap.h"
#include "scene.h"
#include "camera.h"
#include "ray.h"
#include "render_object.h"
#include "light.h"
#include "material.h"

#include <algorithm>
#include <cassert>
#include <cmath>

using osip::Renderer;
using osip::vec3f;

namespace osip
{
    struct Renderer::Implementation
    {
        Bitmap* bitmap;

        Implementation(Bitmap& bitmap) noexcept :
            bitmap{&bitmap}
        {
        }

        Implementation(const Implementation& implementation) noexcept :
            bitmap{implementation.bitmap}
        {
        }

        vec3f trace(const Scene& scene, Ray ray, float bias, unsigned depth) const noexcept;
        void render(const Scene& scene, float bias, unsigned depth) const noexcept;
    };
}

vec3f Renderer::Implementation::trace(const Scene& scene, Ray ray, float bias, unsigned depth) const noexcept
{
    vec3f intersectionPoint;
    const RenderObject* const intersectedObject = scene.getIntersectedObject(ray, &intersectionPoint);

    if (!intersectedObject)
        return {};

    const Material material = intersectedObject->getMaterial();

    const vec3f normal{intersectedObject->normal(intersectionPoint)};

    vec3f color = intersectedObject->color(intersectionPoint) * material.ambient;

    for (Light l : scene.getLights())
    {
        const Ray lightRay{intersectionPoint + normal * bias, (l.position - intersectionPoint).normalize()};

        if (scene.getIntersectedObject(lightRay))
            continue;

        const float brightness = std::max(normal.dot(lightRay.direction), 0.0F);

        const vec3f diffuseComponent{intersectedObject->color(intersectionPoint) * l.color * brightness};

        const vec3f specularComponent{l.color *
                std::pow(std::max(ray.direction.reflect(normal).dot((scene.getCamera().getPosition() -
                                intersectionPoint).normalize()), 0.0F), material.shininess)};

        color += diffuseComponent * material.diffuse + specularComponent * material.specular;
    }

    if (!depth)
        return color;

    if (material.reflection > 0.0F)
    {
        const Ray reflectionRay{intersectionPoint + normal * bias,
            ray.direction.reflect(intersectedObject->normal(intersectionPoint))};

        color += trace(scene, reflectionRay, bias, depth - 1) * material.reflection;
    }

    return color;
}

void Renderer::Implementation::render(const Scene& scene, float bias, unsigned depth) const noexcept
{
    const auto width = bitmap->getWidth();
    const auto height = bitmap->getHeight();

    const float aspectRatio = static_cast<float>(width) / height;

    const float invWidth = 1.0F / width;
    const float invHeight = 1.0F / height;

    const Camera& camera = scene.getCamera();
    const vec3f& cameraPosition = camera.getPosition();
    const Camera::Basis basis = camera.getBasis();

    const float angle = std::tan(camera.getFov() * 0.5F * M_PI / 180.0F);

    for (decltype(bitmap->getWidth()) i = 0; i < width; ++i)
    {
        for (decltype(bitmap->getHeight()) j = 0; j < height; ++j)
        {
            vec3f pixelColor{};

            for (unsigned k = 0; k < 4; ++k)
            {
                for (unsigned l = 0; l < 4; ++l)
                {
                    const float x = (2.0F * (i + (k + 0.5F) * 0.25F) * invWidth - 1.0F) * angle * aspectRatio;
                    const float y = (1.0F - 2.0F * (j + (l + 0.5F) * 0.25F) * invHeight) * angle;

                    const vec3f imagePoint{x * basis.right + y * basis.up + basis.direction + cameraPosition};
                    const Ray cameraRay{cameraPosition, (imagePoint - cameraPosition).normalize()};
                    
                    pixelColor += trace(scene, cameraRay, bias, depth);
                }
            }
            pixelColor *= 255.0F / 16.0F;

            bitmap->setPixel(i, j, {static_cast<uint8_t>(std::min(pixelColor.getX(), 255.0F)),
                                    static_cast<uint8_t>(std::min(pixelColor.getY(), 255.0F)),
                                    static_cast<uint8_t>(std::min(pixelColor.getZ(), 255.0F))});
        }
    }
}

Renderer::Renderer(Bitmap& bitmap) :
    implementation{std::make_unique<Implementation>(bitmap)}
{
}

Renderer::Renderer(const Renderer& renderer) :
    implementation{std::make_unique<Implementation>(*renderer.implementation)}
{
}

Renderer::Renderer(Renderer&&) noexcept = default;

Renderer::~Renderer() = default;

Renderer& Renderer::operator=(const Renderer& renderer)
{
    if (this == &renderer)
        return *this;

    implementation.reset();
    implementation = std::make_unique<Implementation>(*renderer.implementation);

    return *this;
}

Renderer& Renderer::operator=(Renderer&&) noexcept = default;

void Renderer::render(const Scene& scene, float bias, unsigned depth) const noexcept
{
    assert(bias > 0.0F && depth > 0);

    implementation->render(scene, bias, depth);
}

