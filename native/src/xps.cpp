#ifdef SK_BUILD_FOR_WIN

#include <iostream>
#include "core/SkBitmap.h"
#include "core/SkCanvas.h"
#include "core/SkStream.h"
#include "codec/SkCodec.h"
#include "include/core/SkDocument.h"
#include "include/docs/SkXPSDocument.h"

extern "C" {

SkDocument *pdf_document_create(SkDynamicMemoryWStream *stream, PdfDocumentMetadata metadata) {
    return null;
}

}

#endif