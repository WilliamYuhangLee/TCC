/**
 * Created by William Lee on 1/1/19.
 */

#ifndef TCC_UTIL_H
#define TCC_UTIL_H

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef char *string;
string String(char *);

void *checked_malloc(size_t);

#endif //TCC_UTIL_H
