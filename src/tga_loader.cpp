#include "tga_loader.h"
#include "bitmap.h"

using osip::TGALoader;

void TGALoader::write(std::ostream& stream, const Bitmap& bitmap) const
{
    const uint16_t width  = bitmap.getWidth();
    const uint16_t height = bitmap.getHeight();

    const uint8_t header[18]{0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        static_cast<uint8_t>( width  & 0x00FF),
        static_cast<uint8_t>((width  & 0xFF00) >> 8),
        static_cast<uint8_t>( height & 0x00FF),
        static_cast<uint8_t>((height & 0xFF00) >> 8), 24, 0};

    stream.write(reinterpret_cast<const char*>(&header), sizeof header);

    const uint32_t dataLength = width * height;
    const Bitmap::BGR* data = bitmap.getData();

    for (uint32_t i = 0; i < dataLength; ++i)
        stream.write(reinterpret_cast<const char*>(data + i), sizeof(Bitmap::BGR));
}

