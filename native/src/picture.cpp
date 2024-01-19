#include <core/SkStream.h>

#include "include/core/SkPicture.h"


extern "C" {

    SkData* picture_serialize(SkPicture *picture) {
        return picture->serialize().release();
    }

    SkPicture* picture_deserialize(SkData *data) {
        return SkPicture::MakeFromData(data, nullptr).release();
    }

    void picture_delete(SkPicture *picture) {
        delete picture;
    }

}