#include "core/SkBitmap.h"
#include "core/SkRect.h"
#include "codec/SkCodec.h"
#include "include/core/SkData.h"


extern "C" {

SkData *data_create_from_file(const char *path) {
    return SkData::MakeFromFileName(path).release();
}

SkData *data_create_from_binary(const uint8_t* data, int dataLength) {
    return SkData::MakeWithCopy(data, dataLength).release();
}

struct GetBytesFromDataResult {
    int length;
    const uint8_t* bytes;
};

GetBytesFromDataResult data_get_bytes(SkData* data) {
    GetBytesFromDataResult result;
    result.length = data->size();
    result.bytes = data->bytes();

    return result;
}

void data_delete(SkData *data) {
    data->deref();
}

}