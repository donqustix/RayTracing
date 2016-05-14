#ifndef LIGHT_H
#define LIGHT_H

#include "vector_types.h"
#include "vector.h"

namespace osip
{
    struct Light
    {
        vec3f position;
        vec3f color;
    };
}

#endif
