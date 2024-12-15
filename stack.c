#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include <string.h>

Stack * create_stack(int initial_size)
{
	Stack * s = (Stack *)malloc(sizeof(Stack));
	s->contents = (int *)malloc(initial_size*sizeof(Item));
	s->top=0;
	s->size=initial_size;
	return s;
}

void make_empty(Stack * stack)
{
	stack->top = 0;
}

bool is_empty(Stack * stack)
{
	return stack->top == 0;
}

bool is_full(Stack * stack)
{
	return false;
}

void push(Stack * stack, Item i)
{
	if (stack->top>=stack->size-1)
		reallocate(stack);
	stack->contents[stack->top++] = i;
	printf("--Pushded: %d\n", i);
}

Item pop(Stack * stack)
{
	if (is_empty(stack))
		stack_underflow();
	else {
		printf("--Poped: %d\n", stack->contents[stack->top-1]);
		return stack->contents[--stack->top];
	}
	return '\0'; /* prevents compiler warning due to stack_underflow() call */
}

Item peek(Stack *stack)
{
	if (is_empty(stack))
		stack_underflow();
	else
		return stack->contents[stack->top-1];
}

void stack_overflow(void)
{
	printf("Expression is too complex\n");
	exit(EXIT_FAILURE);
}

void stack_underflow(void)
{
	printf("Not enough operands in expression\n");
	printf("something");
	exit(EXIT_FAILURE);
}

static void reallocate(Stack * stack)
{
	int * tmp = (int *)malloc(2*stack->size*sizeof(Item));
	memcpy(tmp, stack->contents, stack->size);
	free(stack->contents);
	stack->contents = tmp;
}

int main() {
    // 스택 생성
    Stack *stack = create_stack(10);

    // 값 푸쉬
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);

    // 값 팝
    pop(stack);
    pop(stack);

    // 현재 스택 최상단 값 확인
    printf("Top of stack: %d\n", peek(stack));

    // 스택 메모리 해제
    free(stack->contents);
    free(stack);

    return 0;  // 프로그램 정상 종료
}
