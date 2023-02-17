#include <assert.h>
#include "types_primitive.h"

int main()
{
    assert(sizeof(tbc_i8_t) == 1);
    assert(sizeof(tbc_i16_t) == 2);
    assert(sizeof(tbc_i32_t) == 4);
    assert(sizeof(tbc_i64_t) == 8);
    assert(sizeof(tbc_u8_t) == 1);
    assert(sizeof(tbc_u16_t) == 2);
    assert(sizeof(tbc_u32_t) == 4);
    assert(sizeof(tbc_u64_t) == 8);
    return 0;
}