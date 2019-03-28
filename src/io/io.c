#include "../queue/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTIONS

// Reads a Process from an input file line [def]
Process *load_process(char *str)
{

  printf("LOADING PROCESS...\n");

  char *delim = " ";

  char *ptr = strtok(str, delim);

  printf("name: '%s'\n", ptr);
  char *name = ptr;

  ptr = strtok(NULL, delim);

  printf("priority: '%s'\n", ptr);
  int priority = atoi(ptr);

  ptr = strtok(NULL, delim);

  printf("t0: '%s'\n", ptr);
  int t0 = atoi(ptr);

  ptr = strtok(NULL, delim);

  printf("n: '%s'\n", ptr);
  int n = atoi(ptr);

  int durations[n * 2 - 1];
  for (int i = 0; i < n * 2 - 1; i++)
  {
    ptr = strtok(NULL, delim);

    printf("duration #%d: '%s'\n", i, ptr);
    durations[i] = atoi(str);
  }

  printf("\n");

  return new_process(name, priority, t0, n, durations);
}

// Reads a Process Queue from an input file [def]
Queue *load_queue(char *path, int max)
{

  char str[max];
  FILE *fp = fopen(path, "r");

  if (!fp)
  {
    printf("Error al abrir '%s'", path);
    return NULL;
  }

  Queue *queue = new_queue();
  while (fgets(str, max, fp))
  {
    add(queue, load_process(str));
  }

  fclose(fp);

  return queue;
}

// Writes the output file [def]
void dump(int n)
{
  ;
}
