#include <iostream>
#include "core/SkBitmap.h"
#include "core/SkCanvas.h"
#include "core/SkStream.h"
#include "codec/SkCodec.h"
#include "include/docs/SkPDFDocument.h"

extern "C" {

SkCanvas *document_begin_page(SkDocument *document, float width, float height) {
    return document->beginPage(width, height);
}

void document_end_page(SkDocument *document) {
    document->endPage();
}

void document_close(SkDocument *document) {
    document->close();
}

void document_delete(SkDocument *document) {
    document->unref();
}

}