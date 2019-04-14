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

// // Inserts a Process into a specific position in a Queue
// void insert(Queue *queue, Process *process, int target)
// {
//   Node *node = new_node(process);

//   queue->length++;

//   // queue is not empty
//   if (queue->tail) // === queue->head
//   {
//     int i = 0;
//     Node *curr = queue->head
//     while (i != target)
//     {

//     }
//   }
// }

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

    // free the Node (but don't touch the Process)
    free(node);

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

// Assigns each process a PID according to its t0 [def]
void assign_pids(Queue *queue)
{
  Process *process;
  int pid = 0;
  int t0 = 0;

  while (pid < queue->length)
  {
    for (int _ = 0; _ < queue->length; _++)
    {
      process = cycle(queue);

      if (process->t0 == t0)
      {
        pid++;
        process->pid = pid;
      }
    }

    t0++;
  }
}

// Returns a Queue sorted by Priority and then by PID [def]
Queue *sorted_queue(Queue *queue)
{
  Queue *sorted = new_queue();
  Process *process;
  int max_priority = 0;
  int max_pid = 0;
  Node *node;

  node = queue->head;
  while (node)
  {
    max_priority = max_priority >= node->value->priority ? max_priority : node->value->priority;
    max_pid = max_pid >= node->value->pid ? max_pid : node->value->pid;

    node = node->next;
  }

  for (int priority = max_priority; priority >= 0; priority--)
  {
    for (int pid = max_pid; pid > 0; pid--)
    {

      for (int _ = 0; _ < queue->length; _++)
      {
        process = cycle(queue);
        // printf("process->pri: %d, pri: %d, process->pid: %d, pid: %d.\n", process->priority, priority, process->pid, pid);

        if (process->priority == priority && process->pid == pid)
        {
          // printf("GO!!\n");
          add(sorted, process);
        }
      }
    }
  }

  return sorted;
}

// // Sorts a Queue by Process' priority [def]
// Queue *priority_sort(Queue * queue)
// {
//   Queue *sorted = new_queue();
//   Process *process;
//   int priority;
//   int i;

//   while (sorted->length != queue->length)
//   {
//     for (priority = 127; priority >= 0; priority--)
//     {
//       for (i = 0; i < queue->length; i++)
//       {
//         process = cycle(queue);

//         if (process->priority == priority)
//         {
//           add(sorted, process);
//         }
//       }
//     }
//   }

//   return sorted;
// }

  // Frees a Queue [def]
  void free_queue(Queue * queue)
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

// Prints a representation of a Queue [def]
void print_queue(Queue *queue)
{
  Node *node = queue->head; // first Node
  // there are still Nodes to be printed
  while (node)
  {
    printf("NODE '%s'(t0: %d)\n", node->value->name, node->value->t0);
    node = node->next;
  }
}
