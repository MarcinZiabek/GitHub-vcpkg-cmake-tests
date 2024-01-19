#include "modules/skparagraph/include/ParagraphStyle.h"
#include "modules/skparagraph/include/ParagraphBuilder.h"
#include "modules/skparagraph/include/TextStyle.h"

extern "C" {

    void paragraph_plan_layout(skia::textlayout::Paragraph* paragraph, float availableWidth) {
        paragraph->layout(availableWidth);
    }

    void paragraph_get_line_heights(skia::textlayout::Paragraph* paragraph, double** array, int* arrayLength) {
        std::vector<skia::textlayout::LineMetrics> lineMetrics;
        paragraph->getLineMetrics(lineMetrics);

        *arrayLength = lineMetrics.size();
        *array = new double[*arrayLength];

        for (int i = 0; i < *arrayLength; ++i)
            (*array)[i] = lineMetrics[i].fHeight;
    }

    void paragraph_get_unresolved_codepoints(skia::textlayout::Paragraph* paragraph, SkUnichar** array, int* arrayLength) {
        const auto codepoints = paragraph->unresolvedCodepoints();

        *arrayLength = codepoints.size();
        *array = new int[*arrayLength];

        int index = 0;

        for (const auto& codepoint : codepoints)
            (*array)[index++] = codepoint;
    }

    void paragraph_get_placeholder_positions(skia::textlayout::Paragraph* paragraph, SkRect** array, int* arrayLength) {
        const auto placeholders = paragraph->getRectsForPlaceholders();

        *arrayLength = placeholders.size();
        *array = new SkRect[*arrayLength];

        for (int i = 0; i < *arrayLength; ++i)
            (*array)[i] = placeholders[i].rect;
    }

    void paragraph_delete(skia::textlayout::Paragraph* paragraph) {
        delete paragraph;
    }

}