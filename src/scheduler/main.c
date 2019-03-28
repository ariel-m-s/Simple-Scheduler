#include "../io/io.h"

#include <stdio.h>

int main()
{
  char *input_path = "data/test1.txt";
  Queue *queue = load_queue(input_path, 1024);

  Node *node = queue->head;
  while(node)
  {
    printf("process->name: '%s", node->value->name);
    node = node->next;
  }

  free_queue(queue);


  return 0;
}
