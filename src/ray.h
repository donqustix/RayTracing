#ifndef RAY_H
#define RAY_H

#include "vector_types.h"
#include "vector.h"

namespace osip
{
    struct Ray
    {
        vec3f position;
        vec3f direction;
    };
}

#endif
