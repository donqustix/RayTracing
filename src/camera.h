#ifndef CAMERA_H
#define CAMERA_H

#include "vector_types.h"
#include "vector.h"

#include <memory>

namespace osip
{
    class Camera
    {
    public:
        struct Basis
        {
            vec3f direction;
            vec3f right;
            vec3f up;
        };

    private:
        struct Implementation;
        std::unique_ptr<Implementation> implementation;

    public:
        Camera();
        Camera(const vec3f& position, const vec3f& viewPoint, float fov = 60.0F);
        Camera(const Camera& camera);
        Camera(Camera&&) noexcept;
        ~Camera();

        Camera& operator=(const Camera& camera);
        Camera& operator=(Camera&&) noexcept;

        const vec3f& getPosition() const noexcept;
        const vec3f& getViewPoint() const noexcept;
        Basis getBasis() const noexcept;
        float getFov() const noexcept;
    };
}

#endif
