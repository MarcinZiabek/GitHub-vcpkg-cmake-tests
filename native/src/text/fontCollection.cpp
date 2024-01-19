#include "modules/skparagraph/include/ParagraphBuilder.h"
#include "modules/skparagraph/include/TypefaceFontProvider.h"

extern "C" {

    struct CreateFontCollectionCommand {
        skia::textlayout::TypefaceFontProvider* typefaceFontProvider;
        bool useGlobalFonts;
        bool enableFontFallback;
    };

    skia::textlayout::FontCollection* font_collection_create(CreateFontCollectionCommand command) {
        auto fontCollection = new skia::textlayout::FontCollection();

        if (command.typefaceFontProvider != nullptr)
            fontCollection->setAssetFontManager(sk_ref_sp(command.typefaceFontProvider));

        if (command.useGlobalFonts)
            fontCollection->setDefaultFontManager(std::move(SkFontMgr::RefDefault()));

        if (command.enableFontFallback) {
            fontCollection->enableFontFallback();
        }
        else {
            fontCollection->disableFontFallback();
        }

        return fontCollection;
    }

    void font_collection_delete(skia::textlayout::FontCollection* fontCollection) {
        delete fontCollection;
    }

}
