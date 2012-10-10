#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

void list_destroy(list_t* list)
{
	assert(list != NULL);

	free(list_clear(list));
}
