// STRUCTURES

// Stats structure
typedef struct
{
  int cpu_count;
  int interruption_count;
  float turnaround_time;
  float response_time;
  float waiting_time;
} Stats;

// FUNCTIONS

// Initializes a new process' statistics [head]
Stats *new_stats();
