#include <iostream>
#include "core/SkBitmap.h"
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "core/SkRect.h"
#include "core/SkStream.h"
#include "codec/SkCodec.h"
#include "include/core/SkCanvas.h"
#include "include/docs/SkPDFDocument.h"
#include "include/core/SkString.h"

extern "C" {

    struct DateTime {
        int16_t timeZoneMinutes;
        uint16_t year;
        uint8_t month;
        uint8_t dayOfWeek;
        uint8_t day;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
    };

    struct PdfDocumentMetadata {
        char *title;
        char *author;
        char *subject;
        char *keywords;
        char *creator;
        char *producer;

        DateTime creationDate;
        DateTime modificationDate;

        bool supportPDFA;
        bool compressDocument;

        SkScalar rasterDPI;
        int imageEncodingQuality;
    };

}

SkTime::DateTime map_datetime(DateTime dateTime) {
    SkTime::DateTime result;

    result.fTimeZoneMinutes = dateTime.timeZoneMinutes;
    result.fYear = dateTime.year;
    result.fMonth = dateTime.month;
    result.fDayOfWeek = dateTime.dayOfWeek;
    result.fDay = dateTime.day;
    result.fHour = dateTime.hour;
    result.fMinute = dateTime.minute;
    result.fSecond = dateTime.second;

    return result;
}

SkPDF::Metadata map_pdf_metadata(PdfDocumentMetadata metadata) {
    SkPDF::Metadata result;

    result.fTitle = metadata.title;
    result.fAuthor = metadata.author;
    result.fSubject = metadata.subject;
    result.fKeywords = metadata.keywords;
    result.fCreator = metadata.creator;
    result.fProducer = metadata.producer;

    result.fCreation = map_datetime(metadata.creationDate);
    result.fModified = map_datetime(metadata.modificationDate);

    result.fRasterDPI = metadata.rasterDPI;
    result.fPDFA = metadata.supportPDFA;
    result.fEncodingQuality = metadata.imageEncodingQuality;
    result.fCompressionLevel = metadata.compressDocument ? SkPDF::Metadata::CompressionLevel::LowButFast : SkPDF::Metadata::CompressionLevel::None;

    return result;
}

extern "C" {

    SkDocument *pdf_document_create(SkDynamicMemoryWStream *stream, PdfDocumentMetadata metadata) {
        return SkPDF::MakeDocument(stream, map_pdf_metadata(metadata)).release();
    }

}