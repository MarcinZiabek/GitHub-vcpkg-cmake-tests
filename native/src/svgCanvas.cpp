#include "core/SkStream.h"
#include "core/SkRect.h"
#include "core/SkCanvas.h"
#include "svg/SkSVGCanvas.h"

extern "C" {

    SkCanvas* svg_create_canvas(SkRect bounds, SkWStream* stream) {
        return SkSVGCanvas::Make(bounds, stream).release();
    }

}