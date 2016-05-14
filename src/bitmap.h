#ifndef BITMAP_H
#define BITMAP_H

#include <memory>
#include <cstdint>

namespace osip
{
    class Bitmap
    {
    public:
        struct BGR
        {
            uint8_t b;
            uint8_t g;
            uint8_t r;
        };

    private:
        struct Implementation;
        std::unique_ptr<Implementation> implementation;

    public:
        Bitmap(uint16_t width, uint16_t height);
        Bitmap(const Bitmap& bitmap);
        Bitmap(Bitmap&&) noexcept;
        ~Bitmap();

        Bitmap& operator=(const Bitmap& bitmap);
        Bitmap& operator=(Bitmap&&) noexcept;

        void clear(uint8_t shade) noexcept;
        void setPixel(uint16_t x, uint16_t y, BGR bgr) noexcept;

        BGR getPixel(uint16_t x, uint16_t y) const noexcept;

        uint16_t getWidth() const noexcept;
        uint16_t getHeight() const noexcept;
        const BGR* getData() const noexcept;
    };
}

#endif
