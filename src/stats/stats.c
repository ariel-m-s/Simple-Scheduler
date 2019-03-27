#include "stats.h"

#include <stdlib.h>

// STRUCTURES

// Stats structure [def]
struct stats
{
  int cpu_count;
  int interruption_count;
  float turnaround_time;
  float response_time;
  float waiting_time;
};

// FUNCTIONS

// Initializes a new process' statistics [def]
Stats *new_stats()
{
  Stats *stats = calloc(1, sizeof(Stats));

  return stats;
}
