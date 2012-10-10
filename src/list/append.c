#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

INLINE static list_t* list_append_node_create(list_node_t* prev, list_t* owner, void* data)
{
	list_node_t* node;

	node = (list_node_t*) malloc(sizeof(list_node_t));

	assert(node != NULL);
	assert(owner != NULL);

	node->next = NULL;
	node->prev = prev;
	node->owner = owner;
	node->data = data;
	owner->last = node;
	owner->len++;

	if (likely(prev != NULL)) {
		assert(prev->next == NULL);
		assert(prev->owner == owner);
		assert(owner->first != NULL);
		prev->next = node;
	} else
		owner->first = node;

	return owner;
}

list_t* list_append(list_t* list, void* data)
{
	return list_append_node_create(list->last, list, data);
}