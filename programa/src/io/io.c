#include "../queue/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTIONS

// Reads a Process from an input file line [def]
Process *load_process(char *str)
{

  char *delim = " ";

  char *ptr = strtok(str, delim);
  char *name = ptr;

  ptr = strtok(NULL, delim);
  int priority = atoi(ptr);

  ptr = strtok(NULL, delim);
  int t0 = atoi(ptr);

  ptr = strtok(NULL, delim);
  int n = atoi(ptr);

  int durations[n * 2 - 1];
  for (int i = 0; i < n * 2 - 1; i++)
  {
    ptr = strtok(NULL, delim);
    durations[i] = atoi(ptr);
  }

  // printf("\n");

  return new_process(name, priority, t0, n, durations);
}

// Reads a Process Queue from an input file [def]
Queue *load_queue(char *path, int max)
{

  char str[max];
  FILE *file = fopen(path, "r");

  if (!file)
  {
    printf("ERROR when opening '%s'", path);
    return NULL;
  }

  Queue *queue = new_queue();
  while (fgets(str, max, file))
  {
    add(queue, load_process(str));
  }

  fclose(file);

  return queue;
}

// Dumps a string representation of the Stats [def]
void dump_stats(FILE *file, Process *process)
{
  fprintf(file, "%s,%d,%d,%d,%d,%d\n", process->name, process->stats->cpu_count, process->stats->interruption_count, process->stats->turnaround_time, process->stats->response_time, process->stats->waiting_time);
}

// Writes the output file [def]
void dump_results(Queue *results, Queue *original, char *path)
{

  FILE *file = fopen(path, "w");
  Process *process;

  int i = 0;
  while (i < results->length)
  {
    process = cycle(results);

    if (process->name == original->head->value->name)
    {
      dump_stats(file, process);
      cycle(original);
      i++;
    }
  }

  fclose(file);
}
