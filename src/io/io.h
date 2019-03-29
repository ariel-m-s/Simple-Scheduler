#include "../queue/queue.h"

#include <stdio.h>

// FUNCTIONS

// Reads a Process from an input file line [head]
Process *load_process(char *str);

// Reads a Process Queue from an input file [head]
Queue *load_queue(char *path, int max);

// Dumps a string representation of the Stats [head]
void dump_stats(FILE *file, Process *process);

// Writes the output file [head]
void dump_results(Queue *results, Queue *order, char *path);
