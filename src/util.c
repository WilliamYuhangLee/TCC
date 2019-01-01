/**
 * Created by William Lee on 1/1/19.
 *
 * Provides commonly used utility functions.
 */

#include "util.h"

#include <stdio.h>
#include <string.h>

void *checked_malloc(size_t size) {
    void *p = malloc(size);
    if (!p) {
        fprintf(stderr, "\nMemory allocation error!\n");
        exit(1);
    }
    return p;
}

string String(char *str) {
    string p = checked_malloc(strlen(str) + 1);
    strcpy(p, str);
    return p;
}
