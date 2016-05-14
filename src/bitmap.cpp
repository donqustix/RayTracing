#include "bitmap.h"

#include <cassert>

using osip::Bitmap;

namespace osip
{
    struct Bitmap::Implementation
    {
        uint16_t width, height;
        std::unique_ptr<BGR[]> data;

        Implementation(uint16_t width, uint16_t height) noexcept :
            width{width}, height{height},
            data{std::make_unique<BGR[]>(width * height)}
        {
            assert(width > 0 && height > 0);
        }

        Implementation(const Implementation& implementation) noexcept :
            width{implementation.width}, height{implementation.height},
            data{std::make_unique<BGR[]>(width * height)}
        {
            const uint32_t dataLength = width * height;

            for (uint32_t i = 0; i < dataLength; ++i)
                data[i] = implementation.data[i];
        }

        void clear(uint8_t shade) noexcept
        {
            const uint32_t dataLength = width * height;

            for (uint32_t i = 0; i < dataLength; ++i)
                data[i] = {shade, shade, shade};
        }

        void setPixel(uint16_t x, uint16_t y, BGR bgr) noexcept
        {
            assert(x < width && y < height);

            data[width * y + x] = bgr;
        }

        BGR getPixel(uint16_t x, uint16_t y) const noexcept
        {
            assert(x < width && y < height);

            return data[width * y + x];
        }
    };
}

Bitmap::Bitmap(uint16_t width, uint16_t height) :
    implementation{std::make_unique<Implementation>(width, height)}
{
}

Bitmap::Bitmap(const Bitmap& bitmap) :
    implementation{std::make_unique<Implementation>(*bitmap.implementation)}
{
}

Bitmap::Bitmap(Bitmap&&) noexcept = default;

Bitmap::~Bitmap() = default;

Bitmap& Bitmap::operator=(const Bitmap& bitmap)
{
    if (this == &bitmap)
        return *this;

    implementation.reset();
    implementation = std::make_unique<Implementation>(*bitmap.implementation);

    return *this;
}

Bitmap& Bitmap::operator=(Bitmap&&) noexcept = default;

void Bitmap::clear(uint8_t shade) noexcept
{
    implementation->clear(shade);
}

void Bitmap::setPixel(uint16_t x, uint16_t y, BGR bgr) noexcept
{
    implementation->setPixel(x, y, bgr);
}

Bitmap::BGR Bitmap::getPixel(uint16_t x, uint16_t y) const noexcept
{
    return implementation->getPixel(x, y);
}

uint16_t Bitmap::getWidth() const noexcept
{
    return implementation->width;
}

uint16_t Bitmap::getHeight() const noexcept
{
    return implementation->height;
}

const Bitmap::BGR* Bitmap::getData() const noexcept
{
    return implementation->data.get();
}

