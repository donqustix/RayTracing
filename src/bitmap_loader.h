#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H

#include <ostream>

namespace osip
{
    class Bitmap;

    struct BitmapLoader
    {
        virtual ~BitmapLoader() = default;
        virtual void write(std::ostream& stream, const Bitmap& bitmap) const = 0;
    };
}

#endif
