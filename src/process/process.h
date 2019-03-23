// Burst type enumeration alias
typedef enum burst_type BurstType;

// State enumeration alias
typedef enum state State;


// Burst structure alias
typedef struct burst Burst;

// Process strucutre alias
typedef struct process Process;


// Initializes a burst header
Burst *new_burst(BurstType type, int duration);

// Initializes a process header
Process *new_process(char *name, int pid, int priority, int t0, int n, int *durations);

// Frees a process header
void free_process(Process *process);
