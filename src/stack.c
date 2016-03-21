#include <stdio.h>
#include <stdlib.h>
#include "../inc/stack.h"

struct Stack_t
{
	int num_stack[MAX_STACK_SIZE];
	int ptr;
};

typedef struct Stack_t Stack_t;
typedef struct Stack_t * pStack_t;

pStack_t pgGameStack;

int stack_init(void)
{
	int result = -1;

	pgGameStack = (pStack_t)malloc(sizeof(Stack_t));

	if (pgGameStack)
	{
		pgGameStack->ptr = 0;
		result = 0;
	}

	return result;
}

void stack_deinit(void)
{
	free(pgGameStack);
}

void stack_clear(void)
{
	if (pgGameStack)
	{
		pgGameStack->ptr = 0;
	}
}

int stack_pop(void)
{
	int result = -1;

	if (pgGameStack)
	{
		if (pgGameStack->ptr)
		{
			result = pgGameStack->num_stack[--pgGameStack->ptr];
			{
				int i;
				printf("\n");
				for (i = 0; i < pgGameStack->ptr; i++)
				{
					printf("%-2d  ", pgGameStack->num_stack[i]);
				}
			}
		}
	}

	return result;
}

int stack_push(int n)
{
	int result = -1;

	if (pgGameStack)
	{
		if (pgGameStack->ptr < MAX_STACK_SIZE)
		{
			pgGameStack->num_stack[pgGameStack->ptr++] = n;
			printf("%-2d  ", n);
			result = 0;
		}
	}

	return result;
}

void print_spacetilltop(void)
{
	if (pgGameStack)
	{
		int i;
		for (i = 0; i < pgGameStack->ptr; i++)
		{
			printf("     ");
		}
	}
}

int stack_first(void)
{
	if (pgGameStack)
	{
		if (pgGameStack->ptr)
		{
			return pgGameStack->num_stack[0];
		}
	}
	return -1;
}

int stack_last(void)
{
	if (pgGameStack)
	{
		if (pgGameStack->ptr)
		{
			return pgGameStack->num_stack[pgGameStack->ptr - 1];
		}
	}
	return -1;
}
