#ifndef _H_DBSCAN
#define _H_DBSCAN
#include "bitvec.h"

unsigned int neighbours_search (
    bitvec_t *out, void *dptr, 
    unsigned int current_point,
    float eps, unsigned int *count
    );

int DBSCAN(void *data, unsigned int *d, unsigned int dlen,
            float eps, unsigned int minpoints,
            unsigned int (*neighbours_search)(bitvec_t *out,
            void *, unsigned int, float, unsigned int *)
    );

#endif