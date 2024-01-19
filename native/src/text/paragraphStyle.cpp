#include <modules/skparagraph/include/ParagraphStyle.h>
#include <modules/skparagraph/include/TextStyle.h>

extern "C" {

    struct ParagraphStyleConfiguration {
        skia::textlayout::TextAlign Alignment;
        skia::textlayout::TextDirection Direction;
        int MaxLinesVisibile;
        char* Ellipsis;
    };

    skia::textlayout::ParagraphStyle* paragraph_style_create(ParagraphStyleConfiguration configuration) {
        auto paragraphStyle = new skia::textlayout::ParagraphStyle();

        paragraphStyle->setTextAlign(configuration.Alignment);
        paragraphStyle->setTextDirection(configuration.Direction);
        paragraphStyle->setEllipsis(SkString(configuration.Ellipsis));
        paragraphStyle->setMaxLines(configuration.MaxLinesVisibile);
        paragraphStyle->setReplaceTabCharacters(true);

        return paragraphStyle;
    }

    void paragraph_style_delete(skia::textlayout::ParagraphStyle* paragraphStyle) {
        delete paragraphStyle;
    }
}
