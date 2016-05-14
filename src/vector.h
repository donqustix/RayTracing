#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

namespace osip
{
    template<typename T>
    class Vector final
    {
        T x, y, z;

    public:
        constexpr Vector() = default;

        constexpr Vector(const T& x, const T& y, const T& z) noexcept :
            x(x), y(y), z(z)
        {
        }

        constexpr Vector& operator+=(const Vector& vector) noexcept
        {
            return *this = *this + vector;
        }

        constexpr Vector& operator-=(const Vector& vector) noexcept
        {
            return *this = *this - vector;
        }

        constexpr Vector& operator*=(const Vector& vector) noexcept
        {
            return *this = *this * vector;
        }

        constexpr Vector& operator/=(const Vector& vector) noexcept
        {
            return *this = *this / vector;
        }

        constexpr Vector& operator*=(const T& value) noexcept
        {
            return *this = *this * value;
        }

        constexpr Vector& operator/=(const T& value) noexcept
        {
            return *this = *this / value;
        }

        constexpr Vector operator+(const Vector& vector) const noexcept
        {
            return {x + vector.x, y + vector.y, z + vector.z};
        }

        constexpr Vector operator-(const Vector& vector) const noexcept
        {
            return {x - vector.x, y - vector.y, z - vector.z};
        }

        constexpr Vector operator-() const noexcept
        {
            return {-x, -y, -z};
        }

        constexpr Vector operator*(const Vector& vector) const noexcept
        {
            return {x * vector.x, y * vector.y, z * vector.z};
        }

        constexpr Vector operator/(const Vector& vector) const noexcept
        {
            return {x / vector.x, y / vector.y, z / vector.z};
        }

        constexpr Vector operator*(const T& value) const noexcept
        {
            return {x * value, y * value, z * value};
        }

        constexpr Vector operator/(const T& value) const noexcept
        {
            return {x / value, y / value, z / value};
        }

        friend constexpr Vector operator*(const T& value, const Vector& vector) noexcept
        {
            return {value * vector.x, value * vector.y, value * vector.z};
        }

        constexpr Vector cross(const Vector& vector) const noexcept
        {
            return {y * vector.z - z * vector.y,
                    z * vector.x - x * vector.z,
                    x * vector.y - y * vector.x};
        }

        constexpr Vector reflect(const Vector& normal) const noexcept
        {
            return *this - 2.0F * normal * dot(normal);
        }

        constexpr Vector normalize() const noexcept
        {
            const T invLength = T(1) / length();

            return {x * invLength, y * invLength, z * invLength};
        }

        constexpr T dot(const Vector& vector) const noexcept
        {
            return x * vector.x + y * vector.y + z * vector.z;
        }

        constexpr T length() const noexcept
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        constexpr const T& getX() const noexcept {return x;}
        constexpr const T& getY() const noexcept {return y;}
        constexpr const T& getZ() const noexcept {return z;}
    };
}

#endif
