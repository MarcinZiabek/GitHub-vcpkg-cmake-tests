
// import qoi from vcpkg package

#include <zlib.h>

extern "C" {

void test() {
    uLong adler = adler32(0L, Z_NULL, 0);
}

}
