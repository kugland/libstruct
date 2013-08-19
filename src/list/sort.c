/*
    File: sort.c

    Copyright (c) 2011 André von Kugland <kugland@gmail.com>

    This software is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write the Free Software Foundation, Inc., 51
    Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#if defined(_MSC_VER)
#  include <intrin.h>
#  if !defined(_WIN64)
#    pragma intrinsic(_BitScanReverse)
#  else
#    pragma intrinsic(_BitScanReverse64)
#  endif
#endif

#include <libstruct/list.h>

#include "../common/libstruct_internal.h"

/**
 * @internal
 *
 * @brief Returns the greatest power of two smaller than n.
 *
 * @param n  an integer value
 * @return   the greatest power of two smaller than n
 */
INLINE static size_t merge_sort_prev_power_2(size_t n)
{
	#if defined(__GNUC__)
		return (1l << sizeof(n) * 8 - __builtin_clzl(n - 1l) - 1l) & LONG_MAX;
	#elif defined(_MSC_VER)
		unsigned long t;
		#if !defined(_WIN64)
			_BitScanReverse(&t, n - 1);
		#else
			_BitScanReverse64(&t, n - 1);
		#endif
		return 1 << t;
	#else
		n--;
		n |= n >> 1;
		n |= n >> 2;
		n |= n >> 4;
		n |= n >> 8;
		if (sizeof(n) >= 4) n |= n >> 16;
		if (sizeof(n) >= 8) n |= n >> 32;
		n++;
		return n >> 1;
	#endif
}

/**
 * @internal
 *
 * @brief Specially optimized version of list_node_create.
 *
 * @param node   node to be linked
 * @param next   its next node
 * @param prev   its previous node
 * @param owner  its owner
 * @param data   its data
 */
INLINE static void merge_sort_node_link(list_node_t* node, list_node_t* next,
	list_node_t* prev, list_t* owner, void* data)
{
	assert(node != NULL);
	assert(owner != NULL);
	assert(next != NULL);
	assert(prev != NULL);
	assert(owner->first != next);
	assert(owner->last != prev);

	node->next = next;
	node->prev = prev;
	node->owner = owner;
	node->data = data;
	prev->next = node;
	next->prev = node;
}

/**
 * @internal
 *
 * @brief Specially optimized version of list_node_destroy.
 *
 * @param node  node to be unlinked
 */
INLINE static void merge_sort_node_unlink(list_node_t* node)
{
	assert(node->prev != NULL);
	assert(node->owner->first != node);

	node->prev->next = node->next;

	if (likely(node->next != NULL)) {
		assert(node->owner->last != node);
		node->next->prev = node->prev;
	} else
		node->owner->last = node->prev;
}

/**
 * @internal
 *
 * @brief Actual implementation of merge sort.
 *
 * @param n1         first node of the sublist
 * @param size       size of the sublist
 * @param cmp        comparator function
 * @param optimsize  is size optimal, i.e. is it a power of two?
 */
static list_node_t* merge_sort(list_node_t* n1, size_t size,
	int (*cmp)(const void *, const void *), int optimsize)
{
	list_node_t *n2, *n3, *nn;
	size_t s1, s2;
	void *tmp;

	assert(n1 != NULL);
	assert(size != 0);
	assert(cmp != NULL);

	if (size > 2) {
		if ((size > 32) && !optimsize) {
			s1 = merge_sort_prev_power_2(size);
			s2 = size - s1;
		} else {
			s2 = size / 2;
			s1 = size - s2;
		}

		n2 = merge_sort(n1, s1, cmp, 1);
		n3 = merge_sort(n2, s2, cmp, optimsize);

		if (cmp(n2->prev->data, n2->data) > 0) {
			while (likely(n1 != n2 && n2 != n3)) {
				if (cmp(n1->data, n2->data) > 0) {
					if (likely(n1->next != n2)) {
						tmp = n2->data;
						nn = n2->next;
						merge_sort_node_unlink(n2);
						merge_sort_node_link(n2, n1->next, n1, n1->owner, n1->data);
						n1->data = tmp;
						n2 = nn;
						n1 = n1->next;
					} else {
						tmp = n1->data;
						n1->data = n2->data;
						n2->data = tmp;
						n2 = n2->next;
					}
				} else
					n1 = n1->next;
			}
		}
		return n3;
	} else {
		if (size == 2) {
			n2 = n1->next;
			n3 = n2->next;
			if (cmp(n1->data, n2->data) > 0) {
				tmp = n1->data;
				n1->data = n2->data;
				n2->data = tmp;
			}
			return n3;
		} else if (size == 1) {
			return n1->next;
		}
	}

	return NULL;
}

/* cf. list.h for documentation. */
list_t* list_sort(list_t* list, int (*cmp)(const void *, const void *))
{
	if (likely(list->len > 1))
		merge_sort(list->first, list->len, cmp, 0);

	return list;
}
