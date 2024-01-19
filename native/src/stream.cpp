#include "core/SkStream.h"


extern "C" {

SkDynamicMemoryWStream *write_stream_create() {
    return new SkDynamicMemoryWStream();
}

void write_stream_delete(SkDynamicMemoryWStream *stream) {
    delete stream;
}

SkData* write_stream_detach_data(SkDynamicMemoryWStream *stream) {
    return stream->detachAsData().release();
}

}