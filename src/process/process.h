#include "../stats/stats.h"

// ENUMERATIONS

// Burst type enumeration
typedef enum burst_type
{
  CPU,
  IO,
} BurstType;

// Process state enumeration
typedef enum process_state
{
  Ghost,
  Ready,
  Running,
  Waiting,
  Finished,
} ProcessState;

// STRUCTURES

// Burst structure
typedef struct burst
{
  BurstType type;
  int duration;
  int runtime;
} Burst;

// Process structure
typedef struct process
{
  char *name;
  int pid; // process id
  int priority;
  int t0; // start time
  int N; // number of bursts (of both types)
  Burst **bursts;
  ProcessState state;
  int curr_burst;
  Stats *stats;
} Process;

// FUNCTIONS

// Initializes a burst [head]
Burst *new_burst(BurstType type, int duration);

// Initializes a Process [head]
Process *new_process(char *name, int priority, int t0, int n, int *durations);

// Frees a Process [head]
void free_process(Process *process);

// Prints a representation of the Stats [head]
void print_stats(Stats *stats);
