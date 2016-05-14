#ifndef TGALOADER_H
#define TGALOADER_H

#include "bitmap_loader.h"

namespace osip
{
    class TGALoader : public BitmapLoader
    {
    public:
        void write(std::ostream& stream, const Bitmap& bitmap) const override;
    };
}

#endif
