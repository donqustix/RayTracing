#ifndef MATERIAL_H
#define MATERIAL_H

namespace osip
{
    struct Material
    {
        float ambient;
        float diffuse;
        float specular;
        float shininess;
        float reflection;
    };
}

#endif
