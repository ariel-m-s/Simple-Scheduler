#include "../process/process.h"

// STRUCTURES

// Node structure [alias]
typedef struct node Node;

// Queue structure [alias]
typedef struct queue Queue;

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

// Frees a Queue [head]
void free_queue(Queue *queue);
