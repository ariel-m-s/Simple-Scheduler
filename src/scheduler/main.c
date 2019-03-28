#include "../io/io.h"

#include <stdio.h>
#include <stdbool.h>

void sim_preemptive()
{
}

void sim_nonpreemptive()
{
}

int main()
{
  Queue *queue = load_queue("data/test1.txt", 1024);

  return 0;
}
