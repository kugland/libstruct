#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

list_t* list_from_array(void** ptr, size_t len)
{
    unsigned i;
    list_t* list;

    list = list_create();

    for (i = 0; i < len; i++)
        list_append(list, ptr[i]);

    return list;
}
