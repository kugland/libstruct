#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "list_internal.h"

list_t* list_clear(list_t* list)
{
	list_node_t* n,* nn;

	assert(list != NULL);

	for (n = list->first; n != NULL; n = nn) {
		nn = n->next;
		if (list->free_data)
			free(n->data);
		free(n);
	}

	list->first = NULL;
	list->last = NULL;
	list->len = 0;

	return list;
}
