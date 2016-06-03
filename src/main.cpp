#include "bitmap.h"
#include "scene.h"
#include "renderer.h"
#include "tga_loader.h"
#include "sphere.h"
#include "vector.h"
#include "material.h"
#include "light.h"
#include "plane.h"

#include <fstream>

using namespace osip;

int main()
{
    Bitmap bitmap{1024, 768};

    Scene scene;
    scene.addRenderObject(new Sphere{{-40.0F, -10.0F, 200.0F}, {1.0F, 0.0F, 0.0F}, 40.0F,
            {0.0F, 1.0F, 1.0F, 50.0F, 0.8F}});
    scene.addRenderObject(new Sphere{{100.0F, 0.0F, 350.0F}, {1.0F, 0.0F, 1.0F}, 50.0F,
            {0.0F, 1.0F, 1.0F, 50.0F, 0.3F}});
    scene.addRenderObject(new Sphere{{40.0F, -40.0F, 150.0F}, {0.0F, 0.0F, 1.0F}, 10.0F,
            {0.0F, 1.0F, 1.0F, 50.0F, 0.2F}});
    scene.addRenderObject(new Sphere{{100.0F, -44.0F, 180.0F}, {1.0F, 1.0F, 0.0F}, 6.0F,
            {0.0F, 1.0F, 1.0F, 50.0F, 0.4F}});
    scene.addRenderObject(new Sphere{{-30.0F, -35.0F, 120.0F}, {0.0F, 1.0F, 1.0F}, 15.0F,
            {0.0F, 1.0F, 1.0F, 50.0F, 0.6F}});
    scene.addRenderObject(new Plane{{0.0F, -50.0F, 0.0F}, {0.0F, -1.0F, 0.0F}, {0.6F, 0.6F, 0.6F},
            {0.0F, 1.0F, 1.0F, 50.0F, 0.4F}});

    scene.addLight({{-100.0F, 300.0F, -50.0F}, {1.0F, 1.0F, 1.0F}});

    Renderer renderer{bitmap};
    renderer.render(scene);

    std::ofstream stream{"image.tga", std::ios::out | std::ios::binary};
    TGALoader tgaLoader;
    tgaLoader.write(stream, bitmap);

    return 0;
}
