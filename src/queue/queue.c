#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

// FUNCTIONS

// Initializes a Node [def]
Node *new_node(Process *process)
{
  Node *node = calloc(1, sizeof(Node));
  node->value = process;
  node->next = NULL;

  return node;
}

// Frees a Node [def]
void free_node(Node *node)
{
  free_process(node->value);
  free(node);
}

// Initializes a Queue [def]
Queue *new_queue()
{
  Queue *queue = calloc(1, sizeof(Queue));

  queue->head = NULL;
  queue->tail = NULL;
  queue->length = 0;

  return queue;
}

// Adds a Process to the tail of a Queue [def]
void add(Queue *queue, Process *process)
{
  Node *node = new_node(process);

  queue->length++;

  // queue is not empty
  if (queue->tail) // === queue->head
  {
    queue->tail->next = node;
  }
  // queue is empty
  else
  {
    queue->head = node;
  }
  queue->tail = node;
}

// Queue not empty ? Pops a Process from the head of a Queue : Pops NULL from a Queue [def]
Process *pop(Queue *queue)
{
  // queue is not empty
  if (queue->head) // === queue->tail
  {

    queue->length--;

    // queue is one node long
    if (queue->head == queue->tail)
    {
      queue->tail = NULL;
    }

    Node *node = queue->head;
    queue->head = node->next;

    Process *process = node->value;

    free_node(node);

    return process;
  }
  // queue is empty
  else
  {
    return NULL;
  }
}

// pop + add [def]
Process *cycle(Queue *queue)
{
  Process *process = pop(queue);
  add(queue, process);

  return process;
}

// Frees a Queue [def]
void free_queue(Queue *queue)
{
  Node *node = queue->head; // first Node
  Node *aux_node;
  // there are still Nodes to be freed
  while (node)
  {
    aux_node = node->next;
    free_node(node);
    node = aux_node;
  }

  free(queue);
}
