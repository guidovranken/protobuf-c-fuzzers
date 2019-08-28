/* 2019 Guido Vranken <guidovranken@gmail.com> */

#include <assert.h>
#include <stdlib.h>
#include <fuzzing/memory.hpp>
#include "test-full.pb-c.h"

#define X(OBJ, PREFIX) \
    { \
        OBJ* msg = PREFIX##__unpack(NULL, size, data); \
        if ( msg != NULL ) { \
            const size_t len = PREFIX##__get_packed_size(msg); \
            uint8_t* copy = (uint8_t*)malloc(len); \
            PREFIX##__pack(msg, copy); \
            fuzzing::memory::memory_test(copy, len); \
            free(copy); \
        } \
        PREFIX##__free_unpacked(msg, NULL); \
    }

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    X(Foo__TestMessSubMess, foo__test_mess_sub_mess);
    X(Foo__TestFieldFlags, foo__test_field_flags);
    X(Foo__TestMessageCheck, foo__test_message_check);
    return 0;
}
