#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "list_internal.h"

list_t* list_apply(list_t* list, void* (*func)(void*, void*), void* context)
{
	list_node_t* node;

	assert(list != NULL);
	assert(func != NULL);

	for (node = list->first; node != NULL; node = node->next)
		node->data = func(node->data, context);

	return list;
}
