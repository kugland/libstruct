#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

list_t* list_filter(list_t* list, int (*func)(void*, void*), void* context)
{
	list_node_t* node,* nn;

	assert(list != NULL);
	assert(func != NULL);

	for (node = list->first; node != NULL; node = nn) {
		nn = node->next;
		if (func(node->data, context) == 0)
			list_node_destroy(node);
	}

	return list;
}
