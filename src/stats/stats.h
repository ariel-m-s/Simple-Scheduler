// STRUCTURES

// Stats structure
typedef struct
{
  int cpu_count;
  int interruption_count;
  int turnaround_time;
  int response_time;
  int waiting_time;
} Stats;

// FUNCTIONS

// Initializes a new process' statistics [head]
Stats *new_stats();
