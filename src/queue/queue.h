#include "../process/process.h"

// STRUCTURES

// Node structure
typedef struct node
{
  Process *value;
  struct node *next;
} Node;

// Queue structure
typedef struct queue
{
  Node *head;
  Node *tail;
  int length;
} Queue;

// FUNCTIONS

// Initializes a Node [head]
Node *new_node(Process *process);

// Frees a Node [head]
void free_node(Node *node);

// Initializes a Queue [head]
Queue *new_queue();

// Adds a Process to the tail of a Queue [head]
void add(Queue *queue, Process *process);

// Queue not empty ? Pops a Process from the head of a Queue : Pops NULL from a Queue [head]
Process *pop(Queue *queue);

// pop + add [head]
Process *cycle(Queue *queue);

// Sorts a Queue by Process' priority [head]
void priority_sort(Queue *queue);

// Frees a Queue [head]
void free_queue(Queue *queue);

// Prints a representation of a Queue
void print_queue(Queue * queue);
