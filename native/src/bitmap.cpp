#include "core/SkBitmap.h"
#include "core/SkImage.h"
#include "core/SkRect.h"
#include "core/SkStream.h"
#include "encode/SkJpegEncoder.h"
#include "encode/SkPngEncoder.h"
#include "encode/SkWebpEncoder.h"


extern "C" {

SkBitmap *bitmap_create(int width, int height) {
    auto bitmap = new SkBitmap();
    bitmap->allocN32Pixels(width, height);
    return bitmap;
}

void bitmap_delete(SkBitmap *bitmap) {
    delete bitmap;
}

SkBitmap *bitmap_load_from_image(SkImage *image) {
    auto targetBitmap = new SkBitmap();
    targetBitmap->allocPixels(image->imageInfo());
    image->readPixels(targetBitmap->pixmap(), 0, 0);
    return targetBitmap;
}

SkData* bitmap_encode_as_jpg(SkBitmap *bitmap, int quality) {
    SkJpegEncoder::Options encodingOptions;
    encodingOptions.fQuality = quality;

    SkDynamicMemoryWStream stream;
    SkJpegEncoder::Encode(&stream, bitmap->pixmap(), encodingOptions);

    return stream.detachAsData().release();
}

SkData* bitmap_encode_as_png(SkBitmap *bitmap) {
    SkPngEncoder::Options encodingOptions;

    SkDynamicMemoryWStream stream;
    SkPngEncoder::Encode(&stream, bitmap->pixmap(), encodingOptions);

    return stream.detachAsData().release();
}

SkData* bitmap_encode_as_webp(SkBitmap *bitmap, int quality) {
    SkWebpEncoder::Options encodingOptions;
    encodingOptions.fCompression = SkWebpEncoder::Compression::kLossy;
    encodingOptions.fQuality = static_cast<float>(quality);

    SkDynamicMemoryWStream stream;
    SkWebpEncoder::Encode(&stream, bitmap->pixmap(), encodingOptions);

    return stream.detachAsData().release();
}

}