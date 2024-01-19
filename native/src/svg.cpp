#include "core/SkStream.h"

#include "modules/svg/include/SkSVGDOM.h"
#include "modules/svg/include/SkSVGSVG.h"
#include "modules/svg/include/SkSVGRenderContext.h"

extern "C" {

    SkSVGDOM* svg_create(SkData* data) {
        auto svgStream = SkMemoryStream(sk_sp(data));
        auto svg = SkSVGDOM::MakeFromStream(svgStream);

        return svg.release();
    }

    void svg_delete(SkSVGDOM* svg) {
        delete svg;
    }

    void svg_get_viewbox(SkSVGDOM* svg, SkRect* size) {
        auto viewBox = svg->getRoot()->getViewBox();
        size->setXYWH(viewBox->left(), viewBox->top(), viewBox->right(), viewBox->bottom());
    }

}