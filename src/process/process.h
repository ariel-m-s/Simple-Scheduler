// ENUMERATIONS

// Burst type enumeration [alias]
typedef enum burst_type BurstType;

// Process state enumeration [alias]
typedef enum process_state ProcessState;

// STRUCTURES

// Burst structure [alias]
typedef struct burst Burst;

// Process strucutre [alias]
typedef struct process Process;

// FUNCTIONS

// Initializes a burst [head]
Burst *new_burst(BurstType type, int duration);

// Initializes a Process [head]
Process *new_process(char *name, int pid, int priority, int t0, int n, int *durations);

// Frees a Process [head]
void free_process(Process *process);
