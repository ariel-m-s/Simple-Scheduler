#include "stats.h"

#include <stdlib.h>

// FUNCTIONS

// Initializes a new process' statistics [def]
Stats *new_stats()
{
  Stats *stats = calloc(1, sizeof(Stats));

  stats->cpu_count = 0;
  stats->interruption_count = 0;
  stats->turnaround_time = 0;
  stats->waiting_time = 0;

  return stats;
}
