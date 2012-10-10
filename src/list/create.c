#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

list_t* list_create(void)
{
	list_t* list;

	list = (list_t*) malloc(sizeof(list_t));

	assert(list != NULL);

	list->first = NULL;
	list->last = NULL;
	list->len = 0;
	list->free_data = 0;

	return list;
}