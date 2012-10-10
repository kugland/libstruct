#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

list_t* list_copy(list_t* list)
{
	assert(list != NULL);

	return list_join(list_create(), list);
}
