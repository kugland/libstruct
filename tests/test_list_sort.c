#include <assert.h>
#include <stdio.h>
#include <time.h>

#include <libstruct/list.h>

unsigned cn, mn;

static unsigned short rnd16(void) { return rand() & 0xffff; }
static unsigned int rnd(void) { return (rnd16() << 16) | rnd16(); }
static int cf(const void* a, const void* b) { return ((int)a) - ((int)b); }

void test_sort(size_t sz)
{
	unsigned i, a;
	int s1=0, s2=0, x1=0, x2=0;
	list_t* l;
	list_node_t* n;

	printf("test_sort(%d) ... ", sz);

	l = list_create();

	for (i = 0; i < sz; i++) {
		a = rnd() % 100;
		if (i % 2)
			list_append(l, (void*)a);
		else
			list_prepend(l, (void*)a);
		s1 += a;
		x1 ^= a;
	}

	list_sort(list_reverse(l), cf);

	for (i = 0, n = l->first; n != NULL; i++, n = n->next) {
		if (n->next)
			assert(cf(n->data, n->next->data) <= 0);

		s2 += (unsigned)n->data;
		x2 ^= (unsigned)n->data;
	}

	assert(s1 == s2);
	assert(x1 == x2);
	assert(i == l->len);

	list_destroy(l);

	printf("ok\n");
}

int main(int argc, char* argv[])
{
	int i;

	//_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	srand(time(NULL));

	for (i = 1000; i < 300000; i++)
		test_sort(i);
	getchar();

	return 0;
}
