#ifndef LIST_H_INCLUDED_C7AFB8232592D6C9BD3705191F02935B
#define LIST_H_INCLUDED_C7AFB8232592D6C9BD3705191F02935B

#include <stdlib.h>

#ifdef __cplusplus 
extern "C" {
#endif

#if defined(__GNUC__)
#define LIST_FA_GCC_MALLOC __attribute__((malloc))
#define LIST_FA_MSC_MALLOC
#elif defined(_MSC_VER)
#define LIST_FA_GCC_MALLOC
#define LIST_FA_MSC_MALLOC __declspec(noalias) __declspec(restrict)
#else
#define LIST_FA_GCC_MALLOC
#define LIST_FA_MSC_MALLOC
#endif

struct list_t;

typedef struct list_node_t {
	void* data;					/**< data held by this node */
	struct list_node_t* next;	/**< next node, null if last */
	struct list_node_t* prev;	/**< prev node, null if first */
	struct list_t* owner;		/**< list that owns this node */
} list_node_t;

typedef struct list_t {
	struct list_node_t* first;	/**< first node of this list */
	struct list_node_t* last;	/**< last node of this list */
	size_t len;					/**< length of the list */
	int free_data;				/**< free data for destroyed nodes? */
} list_t;

LIST_FA_MSC_MALLOC list_t* list_create(void) LIST_FA_GCC_MALLOC;
void list_destroy(list_t*);

/**
 * Creates a node inside an existing list.
 *
 * @param next   its next node (null if it’s the last node of the list)
 * @param prev   its prev node (null if it’s the first node of the list)
 * @param owner  list that will own this node
 * @param data   data of the node
 *
 * @return the newly created node
 */
LIST_FA_MSC_MALLOC list_node_t* list_node_create(list_node_t* next,
	list_node_t* prev, list_t* owner, void* data) LIST_FA_GCC_MALLOC;

/**
 * Destroys a node and unlink it from the list.
 *
 * @param node  the node to be destroyed
 */
void list_node_destroy(list_node_t* node);

/**
 * Removes and destroys all elements from the list.
 *
 * @param list  the list to be destroyed
 */
list_t* list_clear(list_t* list);


LIST_FA_MSC_MALLOC list_t* list_copy(list_t* list) LIST_FA_GCC_MALLOC;
list_t* list_append(list_t*, void*);
list_t* list_prepend(list_t*, void*);
list_t* list_join(list_t* list, list_t* list2);
list_t* list_reverse(list_t* list);

/**
 * Sorts a linked list in-place, using the merge sort algorithm.
 *
 * @param list list to be sorted
 * @param cmp  comparator function
 *
 * @return sorted list
 */
list_t* list_sort(list_t* list, int (*cmp)(const void *, const void *));

/**
 * Converts a list to a void* array.
 *
 * @param list  list to be converted
 *
 * @return void* array
 */
LIST_FA_MSC_MALLOC void** list_to_array(list_t* list) LIST_FA_GCC_MALLOC;

/**
 * Converts a void* array into a list.
 *
 * @param ptr  pointer to the array
 * @param len  length of the array
 *
 * @return list
 */
LIST_FA_MSC_MALLOC list_t* list_from_array(void** ptr, size_t len) LIST_FA_GCC_MALLOC;
list_t* list_apply(list_t* list, void* (*func)(void*, void*), void* context);
list_t* list_filter(list_t* list, int (*func)(void*, void*), void* context);

#ifdef __cplusplus
}
#endif

#endif