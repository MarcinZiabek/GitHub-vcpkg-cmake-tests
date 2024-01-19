#include <modules/skparagraph/include/TextStyle.h>

extern "C" {

    struct TextStyleConfiguration {
        static const int FONT_FAMILIES_LENGTH = 8;

        SkScalar fontSize;
        SkFontStyle fontWeight;

        char* fontFamilies[FONT_FAMILIES_LENGTH];

        SkColor foregroundColor;
        SkColor backgroundColor;

        SkColor decorationColor;
        skia::textlayout::TextDecoration decorationType;
        skia::textlayout::TextDecorationMode decorationMode;
        skia::textlayout::TextDecorationStyle decorationStyle;

        SkScalar letterSpacing;
        SkScalar wordSpacing;
    };

    skia::textlayout::TextStyle* text_style_create(TextStyleConfiguration configuration) {
        auto textStyle = new skia::textlayout::TextStyle();

        textStyle->setFontSize(configuration.fontSize);
        textStyle->setFontStyle(configuration.fontWeight);

        std::vector<SkString> fontFamilies;

        // set font families
        for (auto & fontFamily : configuration.fontFamilies) {
            if (fontFamily == nullptr)
                continue;

            fontFamilies.emplace_back(fontFamily);
        }

        textStyle->setFontFamilies(fontFamilies);
        // end

        if (configuration.foregroundColor != 0) {
            SkPaint paint;
            paint.setColor(configuration.foregroundColor);
            textStyle->setForegroundPaint(paint);
        }

        if (configuration.backgroundColor != 0) {
            SkPaint paint;
            paint.setColor(configuration.backgroundColor);
            textStyle->setBackgroundColor(paint);
        }

        textStyle->setDecorationColor(configuration.decorationColor);
        textStyle->setDecoration(configuration.decorationType);
        textStyle->setDecorationMode(configuration.decorationMode);
        textStyle->setDecorationStyle(configuration.decorationStyle);

        textStyle->setLetterSpacing(configuration.letterSpacing);
        textStyle->setWordSpacing(configuration.wordSpacing);

        return textStyle;
    }

    void text_style_delete(skia::textlayout::TextStyle* textStyle) {
        delete textStyle;
    }
}
