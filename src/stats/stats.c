#include "stats.h"

#include <stdlib.h>

// FUNCTIONS

// Initializes a new process' statistics [def]
Stats *new_stats()
{
  Stats *stats = calloc(1, sizeof(Stats));

  return stats;
}
