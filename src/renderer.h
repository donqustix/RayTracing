#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

namespace osip
{
    class Bitmap;
    class Scene;

    class Renderer
    {
        struct Implementation;
        std::unique_ptr<Implementation> implementation;

    public:
        explicit Renderer(Bitmap& bitmap);
        Renderer(const Renderer& renderer);
        Renderer(Renderer&&) noexcept;
        ~Renderer();

        Renderer& operator=(const Renderer& renderer);
        Renderer& operator=(Renderer&&) noexcept;

        void render(const Scene& scene, float bias = 1e-3F, unsigned depth = 10) const noexcept;
    };
}

#endif
