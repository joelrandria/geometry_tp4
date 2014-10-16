#ifndef __INT_STACK_H__
#define __INT_STACK_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct _int_stack
{
	int value;
	struct _int_stack* next;
} int_stack;

int_stack* int_stack_create(int value);
void int_stack_delete(int_stack* stack);

int_stack* int_stack_push(int_stack* stack, int value);
int_stack* int_stack_pop(int_stack* stack, int* value);

void int_stack_print(int_stack* stack);

#endif
