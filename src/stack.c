#include "stack.h"
#include <stddef.h>
#include <stdlib.h>

stack_t* new_stack() {
  stack_t* nst = (stack_t*) malloc(sizeof(stack_t));
  nst->top = NULL;
  return nst;
}

void free_stack(stack_t * st) {
  node_t * tmp = st->top;
  while(tmp != NULL) {
    st->top = st->top->next;
    free(tmp);
    tmp = st->top;
  }

  free(st);
}

void push_stack(int val, stack_t * st) {
  node_t *newNode = (node_t*) malloc(sizeof(node_t));
  newNode->data = val;
  newNode->next = st->top;
  st->top = newNode;
}

int pop_stack(stack_t * st) {
  if(st->top == NULL) {
    return -1;
  }

  int retval;
  node_t * delNode = st->top;
  st->top = st->top->next;

  retval = delNode->data;
  free(delNode);

  return retval;
}

