#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdbool.h>

typedef struct node {
  struct node* prev;
  int data;
} node_t;

typedef struct queue {
  node_t* head;
  node_t* tail;
  int size;
} queue_t;

queue_t* new_queue();

void free_queue(queue_t*);

int size(queue_t*);

bool isEmpty(queue_t*);

void enqueue(int, queue_t*);

int dequeue(queue_t*);

#endif // _QUEUE_H_
