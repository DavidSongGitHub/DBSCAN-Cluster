#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include "quadtree.h"

#define BITVEC_INS(off, bitvec) bitvec[off / 8] |= (1 << (off % 8))
#define BITVEC_SET(off, bitvec) bitvec[off / 8] & (1 << (off % 8))
#define BITVEC_CLEAR(off, bitvec) bitvec[off / 8] &= ~(1 << (off % 8))

#define popcount(of)  __builtin_popcount(of)


int DBSCAN(void *data, unsigned int *d, unsigned int dlen,
            float eps, unsigned int minpoints,
            unsigned int (*neighbours_search)(char *out,
            void *, unsigned int, float, unsigned int *)
    );


unsigned int neighbours_search (
    char *out, void *dptr,
    unsigned int current_point,
    float eps, unsigned int *count
    );

int main(int argc, char **argv) {

    QUADTREE *ref = NULL;

    unsigned int clusters[6];
    unsigned int expected_clusters1[] = {0,0,0,0,0,0};
    unsigned int expected_clusters2[] = {1,1,1,1,2,2};
    unsigned int expected_clusters3[] = {1,1,1,1,0,0};

    assert(!quadtree_init(&ref, 7, 7));
    // x is the document, y is the label
    assert(quadtree_insert(ref, 0, 1));
    assert(quadtree_insert(ref, 1, 1));
    assert(quadtree_insert(ref, 1, 3));
    assert(quadtree_insert(ref, 2, 0));
    assert(quadtree_insert(ref, 2, 3));
    assert(quadtree_insert(ref, 3, 0));
    assert(quadtree_insert(ref, 4, 2));
    assert(quadtree_insert(ref, 5, 2));
    assert(quadtree_insert(ref, 5, 4));

    for (int i = 0; i < 6; i++) clusters[i] = i;
    assert(!DBSCAN(ref, clusters, 6, 0.005f, 2, &neighbours_search));
    assert(!memcmp(clusters, expected_clusters1, sizeof(unsigned int) * 6));

    for (int i = 0; i < 6; i++) clusters[i] = i;
    assert(!DBSCAN(ref, clusters, 6, 0.67f, 2, &neighbours_search));
    assert(!memcmp(clusters, expected_clusters2, sizeof(unsigned int) * 6));

    for (int i = 0; i < 6; i++) clusters[i] = i;
    assert(!DBSCAN(ref, clusters, 6, 0.67f, 3, &neighbours_search));
    assert(!memcmp(clusters, expected_clusters3, sizeof(unsigned int) * 6));

    return 0;
}