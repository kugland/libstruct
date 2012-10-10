#include <stdlib.h>
#include <assert.h>

#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

void list_node_destroy(list_node_t* node)
{
	assert(node != NULL);
	assert(node->owner != NULL);

	if (node->next != NULL) {
		assert(node->owner->last != node);
		node->next->prev = node->prev;
	} else
		node->owner->last = node->prev;

	if (node->prev != NULL) {
		assert(node->owner->first != node);
		node->prev->next = node->next;
	} else
		node->owner->first = node->next;

	/* decrease owner len */
	node->owner->len--;

	if (node->owner->free_data)
		free(node->data);

	free(node);
}
