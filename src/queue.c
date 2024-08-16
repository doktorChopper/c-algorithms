#include "../include/queue.h"
#include <stddef.h>
#include <stdlib.h>

queue_t* new_queue() {
  queue_t* q = (queue_t*)malloc(sizeof(queue_t));

  q->head = NULL;
  q->tail = NULL;
  q->size = 0;

  return q;
}

void free_queue(queue_t * q) {

  node_t * tmp = q->head;
  while(tmp != NULL) {
    q->head = q->head->prev;
    free(tmp);
    tmp = q->head;
  }

  free(q);
}

int size(queue_t * q) {
  return q->size;
}

bool isEmpty(queue_t * q) {
  return q->size == 0;
}

void enqueue(int val, queue_t * q) {
  node_t* newNode = (node_t*)malloc(sizeof(node_t));
  newNode->prev = NULL;
  newNode->data = val;

  if(q->head == NULL) 
    q->head = newNode;
  else 
    q->tail->prev = newNode;
  q->tail = newNode;

  q->size++;
}

int dequeue(queue_t * q) {
  if(isEmpty(q))
    return -1;
  node_t * del = q->head;
  int retval = del->data;

  q->head = q->head->prev;

  free(del);

  q->size--;
  return retval;
}

