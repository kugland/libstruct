#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "list_internal.h"

list_t* list_reverse(list_t* list)
{
	void *tmp;
	list_node_t* n1,* n2;

	assert(list != NULL);

	for (n1 = list->first, n2 = list->last; n1 != n2 && n2->next != n1;
			n1 = n1->next, n2 = n2->prev) {
		tmp = n1->data;
		n1->data = n2->data;
		n2->data = tmp;
	}

	return list;
}
