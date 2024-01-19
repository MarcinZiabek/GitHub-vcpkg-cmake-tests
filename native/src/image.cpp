#include <iostream>
#include "core/SkBitmap.h"
#include "core/SkCanvas.h"
#include "core/SkImage.h"
#include "core/SkPaint.h"
#include "core/SkRect.h"
#include "core/SkStream.h"
#include "codec/SkCodec.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkData.h"
#include "include/effects/SkImageFilters.h"
#include "include/core/SkPaint.h"
#include "include/effects/SkGradientShader.h"
#include "encode/SkJpegEncoder.h"
#include "encode/SkPngEncoder.h"


extern "C" {

SkImage *image_create_from_data(SkData *data) {
    auto image = SkImages::DeferredFromEncodedData(sk_ref_sp(data));
    return image.release();
}

void image_delete(SkImage *image) {
    image->unref();
}

SkBitmap* image_resize_conditionally(SkImage *image, int targetImageWidth, int targetImageHeight) {
    auto shouldScale = targetImageWidth < image->width() && targetImageHeight < image->height();

    if (shouldScale) {
        auto scaledBitmap = new SkBitmap();
        auto scaledImageInfo = SkImageInfo::Make(targetImageWidth, targetImageHeight, image->colorType(), image->alphaType(), image->refColorSpace());
        scaledBitmap->allocPixels(scaledImageInfo);

        SkSamplingOptions samplingOptions(SkFilterMode::kLinear, SkMipmapMode::kLinear);
        image->scalePixels(scaledBitmap->pixmap(), samplingOptions);

        return scaledBitmap;
    }
    else {
        auto targetBitmap = new SkBitmap();

        targetBitmap->allocPixels(image->imageInfo());
        image->readPixels(targetBitmap->pixmap(), 0, 0);

        return targetBitmap;
    }
}

SkImage *image_resize_and_compress(SkImage *image, int targetImageWidth, int targetImageHeight, int quality) {
    auto scaledBitmap = image_resize_conditionally(image, targetImageWidth, targetImageHeight);

    if (image->isOpaque()) {
        SkJpegEncoder::Options encodingOptions;
        encodingOptions.fQuality = quality;

        SkDynamicMemoryWStream stream;
        SkJpegEncoder::Encode(&stream, scaledBitmap->pixmap(), encodingOptions);
        delete scaledBitmap;

        auto data = stream.detachAsData();
        return SkImages::DeferredFromEncodedData(data).release();
    }
    else {
        SkDynamicMemoryWStream stream;
        SkPngEncoder::Encode(&stream, scaledBitmap->pixmap(), SkPngEncoder::Options());
        delete scaledBitmap;

        auto data = stream.detachAsData();
        return SkImages::DeferredFromEncodedData(data).release();
    }
}

struct SkImageDetails {
    int width;
    int height;

    bool isOpaque;
    int encodedDataSize;
};

SkImageDetails image_get_details(SkImage *image) {
    SkImageDetails details;

    details.width = image->width();
    details.height = image->height();

    details.isOpaque = image->isOpaque();
    details.encodedDataSize = image->refEncodedData()->size();

    return details;
}

SkData* image_get_encoded_data(SkImage* image) {
    return image->refEncodedData().get();
}

SkImage *image_generate_placeholder(int imageWidth, int imageHeight, SkColor firstColor, SkColor secondColor) {
    // generate output
    SkBitmap bitmap;
    bitmap.allocN32Pixels(imageWidth, imageHeight);
    SkCanvas canvas(bitmap);

    // create vertical gradient
    SkPoint points[2] = {SkPoint::Make(0, 0), SkPoint::Make(imageWidth, imageHeight)};
    SkColor colors[] = {firstColor, secondColor };
    auto gradient = SkGradientShader::MakeLinear(points, colors, nullptr, 2, SkTileMode::kDecal);

    // draw gradient
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setDither(true);
    paint.setShader(gradient);
    canvas.drawRect(SkRect::MakeWH(imageWidth, imageHeight), paint);

    // compress image
    SkJpegEncoder::Options encodingOptions;
    encodingOptions.fQuality = 80;

    SkDynamicMemoryWStream stream;
    SkJpegEncoder::Encode(&stream, bitmap.pixmap(), encodingOptions);

    // return result
    auto data = stream.detachAsData();
    return SkImages::DeferredFromEncodedData(data).release();
}

}