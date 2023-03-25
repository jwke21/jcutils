#pragma once

#include "arraylist.h"

/**
 * Helper function that resizes the given array list by doubling the capacity.
*/
void resize(arraylist_t *al)
{
    al->capacity *= 2;
    al->data = realloc(al->data, al->capacity);
    assert(al->data != NULL); // check that relloc was successful
}

void al_add(arraylist_t *al, void *new_e)
{
    // check if resizing is necessary
    if (al->element_size == al->capacity) {
        resize(al);
    }
    memcpy(&al->data[al->size], new_e, al->element_size);
    al->size++;
}

void al_clear(arraylist_t *al)
{
    ju_size_t cleared_bytes = al->size * al->element_size;
    bzero(al->data, cleared_bytes);
    al->size = 0;
}

boolean al_contains(arraylist_t *al, void *target)
{
    // check if target is pointer to existing element in arraylist
    if (al->data <= target && &al->data[al->size - 1] >= target) {
        return TRUE;
    }
    // check by value
    void *cur;
    ju_size_t e_size = al->element_size;
    for (int i = 0; i < al->size - 1; i++) {
        cur = &al->data[i];
        if (memcmp(cur, target, e_size) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

arraylist_t *al_create(comparison_func_t *comparator, const ju_size_t init_capacity, const ju_size_t elem_size)
{
    arraylist_t *ret = calloc(1, sizeof(arraylist_t));
    assert(ret != NULL);
    ret->data = calloc(init_capacity, elem_size);
    assert(ret->data != NULL);
    ret->comparator = comparator;
    assert(ret->comparator != NULL);
    ret->capacity = init_capacity;
    ret->element_size = elem_size;
    return ret;
}

arraylist_t *al_create_default(comparison_func_t* comparator, const ju_size_t elem_size)
{
    arraylist_t *ret = calloc(1, sizeof(arraylist_t));
    assert(ret != NULL);
    ret->data = calloc(DEFAULT_ARRAYLIST_INIT_CAPACITY, elem_size);
    assert(ret->data != NULL);
    ret->comparator = comparator;
    assert(ret->comparator != NULL);
    ret->capacity = DEFAULT_ARRAYLIST_INIT_CAPACITY;
    ret->element_size = elem_size;
    return ret;
}

