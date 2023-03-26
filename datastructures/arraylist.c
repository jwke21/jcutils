#pragma once

#include "arraylist.h"

#define OFFSET(arr, i, size) arr + i * size

/**
 * Helper function that resizes the given array list by doubling the capacity.
*/
void resize(arraylist_t *al)
{
    al->capacity *= 2;
    al->data = realloc(al->data, al->capacity * al->element_size);
    assert(al->data != NULL); // check that relloc was successful
}

void al_add(arraylist_t *al, const void *new_e)
{
    // check if resizing is necessary
    if (al->element_size == al->capacity) {
        resize(al);
    }
    memcpy(OFFSET(al->data, al->size, al->element_size), new_e, al->element_size);
    al->size++;
}

void al_clear(arraylist_t *al)
{
    size_t cleared_bytes = al->size * al->element_size;
    bzero(al->data, cleared_bytes);
    al->size = 0;
}

boolean al_contains(arraylist_t *al, const void *target)
{
    // check if target is pointer to existing element in arraylist
    void *data = al->data;
    size_t e_size = al->element_size;
    if (data <= target && OFFSET(data, al->size - 1, e_size) >= target) {
        return TRUE;
    }
    // check by value
    void *cur;
    for (size_t i = 0; i < al->size - 1; i++) {
        cur = OFFSET(data, i, e_size);
        if (memcmp(cur, target, e_size) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

arraylist_t *al_create(comparison_func_t comparator, const size_t init_capacity, const size_t elem_size)
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

arraylist_t *al_create_default(comparison_func_t comparator, const size_t elem_size)
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

void al_destroy(arraylist_t *al)
{
    free(al->data);
    free(al);
}

void *al_get(arraylist_t *al, const size_t index, void *buf)
{
    if (index >= al->size) {
        return NULL;
    }
    memcpy(buf, OFFSET(al->data, index, al->element_size), al->element_size);
    return buf;
}

int index_of(arraylist_t *al, const void *target)
{
    void *cur, *data = al->data;
    size_t e_size = al->element_size;
    for (size_t i = 0; i < al->size; i++) {
        cur = OFFSET(data, i, e_size);
        if (memcmp(cur, target, e_size) == 0) {
            return i;
        }
    }
    return -1;
}

void remove_at(arraylist_t *al, const size_t index)
{
    if (index >= al->size) {
        return;
    }
    size_t e_size = al->element_size;
    void *data = al->data;
    for (size_t i = index + 1; i < al->size; i++) {
        memcpy(OFFSET(data, i - 1, e_size), OFFSET(data, i, e_size), e_size);
    }
    al->size--;
}

void al_remove_elem(arraylist_t *al, const void *target)
{
    size_t i, e_size = al->element_size;
    void *cur, *data = al->data, *removed = NULL;
    for (i = 0; i < al->size; i++) {
        cur = OFFSET(data, i, e_size);
        if (memcmp(cur, target, e_size) == 0) {
            removed = cur;
            break;
        }
    }
    // if target is not in the arraylist
    if (removed == NULL) {
        return;
    }
    for (i = i + 1; i < al->size; i++) {
        memcpy(OFFSET(data, i - 1, e_size), OFFSET(data, i, e_size), e_size);
    }
    al->size--;
}

void al_replace(arraylist_t *al, const size_t old_e_i, const void *new_e)
{
    if (old_e_i >= al->size) {
        return;
    }
    size_t e_size = al->element_size;
    memcpy(OFFSET(al->data, old_e_i, e_size), new_e, e_size);
}

size_t al_size(arraylist_t *al)
{
    return al->size;
}

void al_sort(arraylist_t *al)
{
    qsort(al->data, al->size, al->element_size, al->comparator);
}
