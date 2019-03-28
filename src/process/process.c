#include "process.h"

#include <stdlib.h>
#include <stdio.h>

// FUNCTIONS

// Initializes a burst
Burst *new_burst(BurstType type, int duration)
{
  Burst *burst = calloc(1, sizeof(Burst));
  burst->type = type;
  burst->duration = duration;

  return burst;
}

// Initializes a Process
Process *new_process(char *name, int priority, int t0, int n, int *durations)
{
  Process *process = calloc(1, sizeof(Process));

  process->pid = 0;
  process->priority = priority;
  process->t0 = t0;
  process->state = Ready;
  process->curr_burst_runtime = 0;
  process->stats = new_stats();

  // Assign the name
  process->name = calloc(256, sizeof(char));
  for (int i = 0; i < sizeof(name) / sizeof(char); i++)
  {
    (process->name)[i] = name[i];
  }

  // Assign the bursts
  process->bursts = calloc(n, sizeof(Burst));
  for (int i = 0; i < n * 2 - 1; i++)
  {
    BurstType type = i % 2 ? IO : CPU;
    Burst *burst = new_burst(type, durations[i]);
    process->bursts[i] = *burst;
  }

  return process;
}

// Frees a Process
void free_process(Process *process)
{
  free(process->name);
  free(process->bursts);
  free(process->stats);

  free(process);
}

