/* Minimal Linux-like double-linked list helper functions test
 *
 * Copyright (c) 2012-2014, Sven Eckelmann <sven@narfation.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "../list.h"
#include <assert.h>
#include <stdlib.h>

struct listitem {
	int i;
	struct hlist_node list;
};

int main(void)
{
	struct hlist_head testlist;
	struct listitem *item;
	struct hlist_node *lis;
	int i;

	INIT_HLIST_HEAD(&testlist);

	assert(hlist_empty(&testlist));

	for (i = 0; i < 5; i++) {
		item = (struct listitem *)malloc(sizeof(*item));
		assert(item);
		item->i = i;
		hlist_add_head(&item->list, &testlist);
	}

	assert(!hlist_empty(&testlist));

	i = 4;
	hlist_for_each_entry_t(item, &testlist, struct listitem, list) {
		assert(item->i == i);
		i--;
	}
	assert(i == -1);

	assert(!hlist_empty(&testlist));

	i = 4;
	hlist_for_each_entry_safe_t(item, lis, &testlist, struct listitem,
				    list) {
		assert(item->i == i);
		hlist_del(&item->list);
		free(item);
		i--;
	}

	assert(i == -1);
	assert(hlist_empty(&testlist));

	return 0;
}
