#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "jcutils_common.h"

#define JCU_AL_DEFAULT_INIT_CAPACITY 8

/**
 * Type definition for arraylists. They will be dynamically resized upon adding
 * an element that would cause the size to exceed the capcity. This data
 * structure is not threadsafe.
*/
typedef struct arraylist {
    size_t size;
    size_t capacity;
    size_t element_size;
    comparison_func_t comparator;
    void *data;
} arraylist_t;

/**
 * Appends an element to the end of arraylist. Creates a deep copy of the
 * element in the arraylist.
 * 
 * @param al Pointer to arraylist that will be added to.
 * @param new_e Element that will be appended to the end of the arraylist.
*/
void al_add(arraylist_t *al, const void *new_e);

/**
 * Removes all elements from the arraylist.
 * 
 * @param al Pointer to the arraylist to be cleared.
*/
void al_clear(arraylist_t *al);

/**
 * Checks if the arraylist contains the target element. Searches by value so
 * the given target pointer does not have to be (but can be) a pointer to an
 * an existing element in the list.
 * 
 * @param al Pointer to the arraylist that will be searched.
 * @param target Pointer to the element that will be searched for.
 * 
 * @returns True (i.e. 1) if the element is in the arraylist, otherwise False
 * (i.e. 0).
*/
boolean al_contains(arraylist_t *al, const void *target);

/**
 * Creates an arraylist that will store elements of the specified size.
 * Initializes the capacity to the given initial capacity. Will allocate space
 * for the arraylist on the heap such that al_destroy must be called to avoid
 * memory leaks.
 * 
 * @param comparator Function that defines the comparison relation between data
 * elements.
 * @param initial_capacity The initial capacity of the arraylist.
 * @param elem_size The size of the data elements that the arraylist will hold.
 * 
 * @returns Pointer to the initialized arraylist.
*/
arraylist_t *al_create(comparison_func_t comparator, const size_t init_capacity, const size_t elem_size);

/**
 * Creates an array list that will store elements of the specified size.
 * Initializes the capacity to the default capacity of 8. Will allocate space
 * for the arraylist on the heap such that al_destroy must be called to avoid
 * memory leaks.
 * 
 * @param comparator Function that defines the comparison relation between data
 * elements.
 * @param elem_size The size of the data elements that the arraylist will hold.
 * 
 * @returns Pointer to the initialized arraylist.
*/
arraylist_t *al_create_default(comparison_func_t comparator, const size_t elem_size);

/**
 * Destroys the arraylist at the given pointer and frees the heap memory
 * associated with it.
 * 
 * @param al Pointer to the arraylist that will be destroyed.
*/
void al_destroy(arraylist_t *al);

/**
 * Copies the element at the given index from the arraylist into the given
 * buffer. Will not modify the buffer if the index is out of bounds: if index
 * < 0 or >= size.
 * 
 * @param al Pointer to the arraylist that will be operated on.
 * @param index Index of the target element in the arraylist.
 * @param buf Buffer that arraylist element will be copied into.
 * 
 * @returns The buffer pointer.
*/
void *al_get(arraylist_t *al, const size_t index, void *buf);

/**
 * Finds the index of the given element in the arraylist or -1 if the element
 * is not present. Searches by value so the given target pointer does not
 * have to be (but can be) a pointer to an existing element in the arraylist.
 * 
 * @param al Pointer to the arraylist that will be operated on.
 * @param target Pointer to the element that will be searched for.
 * 
 * @returns Index of the target element in the arraylist or -1.
*/
int al_index_of(arraylist_t *al, const void *target);

/**
 * Removes the element at the given element from the arraylist. Does nothing
 * if the index is out of bounds.
 * 
 * @param al Pointer to arraylist that will be operated on.
 * @param index Index of the element that will be removed from the list.
*/
void al_remove_at(arraylist_t *al, const size_t index);

/**
 * Removes the first element matching the target at the given pointer from the
 * arraylist. Searches by value so the given target pointer does not have to be
 * (but can be) a pointer to an existing element in the arraylist. Does nothing
 * if there are no elements in the arraylist that match the target.
 * 
 * @param al Pointer to arraylist that will be operated on.
 * @param target Pointer to the element that will be removed from the list.
 */
void al_remove_elem(arraylist_t *al, const void *target);

/**
 * Replace the old element at the given index with the value at the given
 * new element pointer. Copies the new element's value into the location of
 * the old element. Does nothing if the index is out of bound.
 * 
 * @param al Pointer to the arraylist that will be operated on.
 * @param old_e_i Index of the element that will be replaced.
 * @param new_e Pointer to the new element that will replace the old element.
 */
void al_replace(arraylist_t *al, const size_t old_e_i, const void *new_e);

/**
 * The number of elements in the arraylist.
 * 
 * @param al Pointer to arraylist whose size will be checked.
 * 
 * @return Size of the arraylist (i.e. number of elements).
 */
size_t al_size(arraylist_t *al);

/**
 * Sorts the arraylist in ascending order. Uses the qsort function of stdlib.h.
 * The comparator function given at initialization is used to define ordering.
 * 
 * @param al Pointer to arraylist that will be sorted.
 */
void al_sort(arraylist_t *al);

#endif // ARRAYLIST_H
