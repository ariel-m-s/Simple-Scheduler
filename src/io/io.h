#include "../queue/queue.h"

// FUNCTIONS

// Reads a Process from an input file line [head]
Process *load_process(char *str);

// Reads a Process Queue from an input file [head]
Queue *load(char *path, int max);

// Writes the output file [head]
void dump();
