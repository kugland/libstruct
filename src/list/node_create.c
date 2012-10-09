#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "list_internal.h"

list_node_t* list_node_create(list_node_t* next, list_node_t* prev, list_t* owner, void* data)
{
	list_node_t* node;

	assert(node != NULL);
	assert(owner != NULL);

	node = (list_node_t*) malloc(sizeof(list_node_t));

	node->next = next;
	node->prev = prev;
	node->owner = owner;
	node->data = data;

	if (next != NULL) {
		assert(next->prev == prev);
		assert(next->owner == owner);
		assert(owner->last != prev);
		next->prev = node;
	} else
		owner->last = node;

	if (prev != NULL) {
		assert(prev->next == next);
		assert(prev->owner == owner);
		assert(owner->first != next);
		prev->next = node;
	} else
		owner->first = node;

	owner->len++;

	return node;
}
