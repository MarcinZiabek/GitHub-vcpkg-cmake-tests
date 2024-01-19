#include "modules/skparagraph/include/ParagraphStyle.h"
#include "modules/skparagraph/include/ParagraphBuilder.h"
#include "modules/skparagraph/include/TextStyle.h"

extern "C" {

    skia::textlayout::ParagraphBuilder* paragraph_builder_create(skia::textlayout::ParagraphStyle* paragraphStyle, skia::textlayout::FontCollection* fontCollection) {
        auto paragraphBuilder = skia::textlayout::ParagraphBuilder::make(*paragraphStyle, sk_ref_sp(fontCollection));
        return paragraphBuilder.release();
    }

    void paragraph_builder_add_text(skia::textlayout::ParagraphBuilder* paragraphBuilder, char* text, skia::textlayout::TextStyle* style) {
        paragraphBuilder->pushStyle(*style);
        paragraphBuilder->addText(text);
        paragraphBuilder->pop();
    }

    void paragraph_builder_add_placeholder(skia::textlayout::ParagraphBuilder* paragraphBuilder, skia::textlayout::PlaceholderStyle style) {
        paragraphBuilder->addPlaceholder(style);
    }

    skia::textlayout::Paragraph* paragraph_builder_create_paragraph(skia::textlayout::ParagraphBuilder* paragraphBuilder) {
        auto paragraph = paragraphBuilder->Build();
        return paragraph.release();
    }

    void paragraph_builder_delete(skia::textlayout::ParagraphBuilder* paragraphBuilder) {
        delete paragraphBuilder;
    }

}  