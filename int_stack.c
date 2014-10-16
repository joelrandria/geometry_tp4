#include "int_stack.h"

int_stack* int_stack_create(int value)
{
	int_stack* stack;

	stack = malloc(sizeof(*stack));
	stack->value = value;
	stack->next = 0;

	return stack;
}
void int_stack_delete(int_stack* stack)
{
	if (stack == 0)
		return;

	if (stack->next)
		int_stack_delete(stack->next);

	free(stack);
}

int_stack* int_stack_push(int_stack* stack, int value)
{
	int_stack* head;

	head = int_stack_create(value);
	head->next = stack;

	return head;
}
int_stack* int_stack_pop(int_stack* stack, int* value)
{
	int_stack* next;

	next = stack->next;
	*value = stack->value;

	free(stack);

	return next;
}

void int_stack_print(int_stack* stack)
{
	printf("[");
	while (stack)
	{
		printf("%d", stack->value);
		if (stack->next)
			printf(" ");
		stack = stack->next;
	}
	printf("]\r\n");
}
