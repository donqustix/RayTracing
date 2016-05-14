#include "scene.h"
#include "camera.h"
#include "light.h"
#include "ray.h"
#include "render_object.h"

using osip::Scene;
using osip::Camera;
using osip::RenderObject;
using osip::Light;

namespace osip
{
    struct Scene::Implementation
    {
        std::vector<std::unique_ptr<RenderObject>> renderObjects;
        std::vector<Light> lights;
        Camera camera;
    };
}

Scene::Scene() :
    implementation{std::make_unique<Implementation>()}
{
}

Scene::Scene(Scene&&) noexcept = default;

Scene::~Scene() = default;

Scene& Scene::operator=(Scene&&) noexcept = default;

void Scene::addRenderObject(RenderObject* renderObject)
{
    implementation->renderObjects.push_back(std::unique_ptr<RenderObject>{renderObject});
}

void Scene::addLight(Light light)
{
    implementation->lights.push_back(light);
}

const RenderObject* Scene::getIntersectedObject(Ray ray, vec3f* intersectionPoint) const noexcept
{
    const auto& renderObjects = implementation->renderObjects;
    if (renderObjects.empty())
        return nullptr;

    struct IntersectionData
    {
        bool intersect;
        float t;
        const RenderObject* renderObject;
        vec3f intersectionPoint;
    } temp{};

    for (decltype(implementation->renderObjects)::const_iterator iter = renderObjects.cbegin();
            iter != renderObjects.cend(); ++iter)
    {
        IntersectionData intersectionData;
        intersectionData.renderObject = iter->get();
        intersectionData.intersect = (*iter)->intersect(ray, &intersectionData.t,
                &intersectionData.intersectionPoint);

        if (intersectionData.intersect)
        {
            if (temp.intersect)
            {
                if (temp.t > intersectionData.t)
                    temp   = intersectionData;
            }
            else
                temp = intersectionData;
        }
    }

    if (temp.intersect)
    {
        if (intersectionPoint)
            *intersectionPoint = temp.intersectionPoint;

        return temp.renderObject;
    }

    return nullptr;
}

const std::vector<Light>& Scene::getLights() const noexcept
{
    return implementation->lights;
}

const Camera& Scene::getCamera() const noexcept
{
    return implementation->camera;
}

