#ifndef _STACK_H_
#define _STACK_H_

typedef struct node{
  struct node* next;
  int data;
} node_t;

typedef struct {
  struct node *top;
} stack_t;

stack_t* new_stack();

void free_stack(stack_t*);

void push_stack(int, stack_t*);

int pop_stack(stack_t*);

#endif // _STACK_H_
