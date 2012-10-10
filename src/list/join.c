#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

list_t* list_join(list_t* list, list_t* list2)
{
	list_node_t* node;

	assert(list != NULL);
	assert(list2 != NULL);

	for (node = list2->first; node != NULL; node = node->next)
		list_append(list, node->data);

	return list;
}
