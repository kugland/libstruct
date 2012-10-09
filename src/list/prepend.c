#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "list_internal.h"

INLINE static void prepend_list_node_create(list_node_t* next, list_t* owner, void* data)
{
	list_node_t* node;

	node = (list_node_t*) malloc(sizeof(list_node_t));

	assert(node != NULL);
	assert(owner != NULL);

	node->next = next;
	node->prev = NULL;
	node->owner = owner;
	node->data = data;
	owner->first = node;
	owner->len++;

	if (likely(next != NULL)) {
		assert(next->prev == NULL);
		assert(next->owner == owner);
		assert(owner->last != NULL);
		next->prev = node;
	} else 
		owner->last = node;
}

list_t* list_prepend(list_t* list, void* data)
{
	prepend_list_node_create(list->first, list, data);

	return list;
}
