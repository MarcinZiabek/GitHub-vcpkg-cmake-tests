#include "modules/skparagraph/include/ParagraphBuilder.h"
#include "modules/skparagraph/include/TypefaceFontProvider.h"

extern "C" {

    skia::textlayout::TypefaceFontProvider* typeface_font_provider_create() {
        return sk_make_sp<skia::textlayout::TypefaceFontProvider>().release();
    }

    void typeface_font_provider_add_typeface(skia::textlayout::TypefaceFontProvider* typefaceFontProvider, SkData* typefaceData) {
        auto typeface = SkTypeface::MakeFromData(sk_ref_sp(typefaceData));
        typefaceFontProvider->registerTypeface(typeface);
    }

    void typeface_font_provider_add_typeface_with_custom_alias(skia::textlayout::TypefaceFontProvider* typefaceFontProvider, SkData* typefaceData, char* alias) {
        auto typeface = SkTypeface::MakeFromData(sk_ref_sp(typefaceData));
        typefaceFontProvider->registerTypeface(typeface, SkString(alias));
    }

    void typeface_font_provider_delete(skia::textlayout::TypefaceFontProvider* typefaceFontProvider) {
        delete typefaceFontProvider;
    }

}
