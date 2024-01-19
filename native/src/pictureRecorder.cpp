#include "include/core/SkPicture.h"
#include "include/core/SkPictureRecorder.h"

extern "C" {

    SkPictureRecorder *picture_recorder_create() {
        return new SkPictureRecorder();
    }

    SkCanvas *picture_recorder_begin_recording(SkPictureRecorder *pictureRecorder, float width, float height) {
        return pictureRecorder->beginRecording(width, height);
    }

    SkPicture *picture_recorder_end_recording(SkPictureRecorder *pictureRecorder) {
        return pictureRecorder->finishRecordingAsPicture().release();
    }

    void picture_recorder_delete(SkPictureRecorder *pictureRecorder) {
        delete pictureRecorder;
    }

}