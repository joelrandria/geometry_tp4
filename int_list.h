#ifndef __INT_LIST_H__
#define __INT_LIST_H__

#include <stdlib.h>

typedef struct _int_list
{
	int value;
	struct _int_list* next;
} int_list;

int_list* int_list_create(int value);
int_list* int_list_enqueue(int_list* list, int value);

unsigned int int_list_size(int_list* list);
int_list* int_list_last(int_list* list);

#endif
