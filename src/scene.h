#ifndef SCENE_H
#define SCENE_H

#include "vector_types.h"

#include <memory>
#include <vector>

namespace osip
{
    class RenderObject;
    class Camera;
    struct Light;
    struct Ray;

    class Scene
    {
        struct Implementation;
        std::unique_ptr<Implementation> implementation;

    public:
        Scene();
        Scene(const Scene& scene) = delete;
        Scene(Scene&&) noexcept;
        ~Scene();

        Scene& operator=(const Scene& scene) = delete;
        Scene& operator=(Scene&&) noexcept;

        void addRenderObject(RenderObject* renderObject);
        void addLight(Light light);

        const RenderObject* getIntersectedObject(Ray ray,
                vec3f* intersectionPoint = nullptr) const noexcept;

        const std::vector<Light>& getLights() const noexcept;
        const Camera& getCamera() const noexcept;
    };
}

#endif
