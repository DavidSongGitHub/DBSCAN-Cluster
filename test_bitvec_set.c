#include <assert.h>
#include "bitvec.h"

int main(int argc, char **argv) {
    bitvec_t *b = NULL;
    assert(!bitvec_alloc(&b, 1));

    bitvec_set(b, 0);
    assert(b->storage[0] == 0x1);

    return 0;
}