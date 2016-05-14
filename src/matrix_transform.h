#ifndef MATRIXTRANSFORM_H
#define MATRIXTRANSFORM_H

#include "matrix.h"

namespace osip
{
    template<typename T>
    Matrix<T> createTranslationMatrix(const T& x, const T& y) noexcept
    {
        return 
        {
            {
                1.0F, 0.0F, 0.0F, x,
                0.0F, 1.0F, 0.0F, y,
                0.0F, 0.0F, 1.0F, 0.0F,
                0.0F, 0.0F, 0.0F, 1.0F
            }
        };
    }
}

#endif
