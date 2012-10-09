#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "list_internal.h"

void** list_to_array(list_t* list)
{
	int i;
	list_node_t* node;
	void** ptr;

	ptr = malloc(sizeof(void*) * list->len);

	assert(list != NULL);
	assert(ptr != NULL);

	for (node = list->first, i = 0; node != NULL; node = node->next, i++)
		ptr[i] = node->data;

	return ptr;
}
