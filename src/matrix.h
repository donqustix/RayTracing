#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

namespace osip
{
    template<typename T>
    class Matrix final
    {
        T data[16];

    public:
        constexpr Matrix() = default;

        constexpr Matrix(const T (&data)[16]) noexcept
        {
            *this = data;
        }

        constexpr Matrix& operator=(const T (&data)[16]) noexcept
        {
            for (unsigned i = 0; i < 16; ++i)
                *(this->data + i) = *(data + i);

            return *this;
        }

        constexpr Matrix operator*(const Matrix& matrix) const noexcept
        {
            Matrix temp{};

            for (unsigned i = 0; i < 4; ++ i)
                for (unsigned j = 0; j < 4; ++j)
                    for (unsigned k = 0; k < 4; ++k)
                        temp(i, j) += (*this)(i, k) * matrix(k, j);

            return temp;
        }

        constexpr Vector<T> operator*(const Vector<T>& vector) const noexcept
        {
            return 
            {
                vector.getX() * (*this)(0, 0) + vector.getY() * (*this)(0, 1) +
                vector.getZ() * (*this)(0, 2) + (*this)(0, 3),
                vector.getX() * (*this)(1, 0) + vector.getY() * (*this)(1, 1) +
                vector.getZ() * (*this)(1, 2) + (*this)(1, 3),
                vector.getX() * (*this)(2, 0) + vector.getY() * (*this)(2, 1) +
                vector.getZ() * (*this)(2, 2) + (*this)(2, 3)
            };
        }

        constexpr const T& operator()(unsigned row, unsigned col) const noexcept
        {
            return *(data + 4 * row + col);
        }

        constexpr T& operator()(unsigned row, unsigned col) noexcept
        {
            return *(data + 4 * row + col);
        }

        constexpr const T* getData() const noexcept {return data;}
    };
}

#endif
