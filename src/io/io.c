#include "../process/process.h"
#include "../queue/queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUNCTIONS

// Reads a Process from an input file line [def]
Process *load_process(char *str)
{
  char *delim = " ";
  char *ptr = strtok(str, delim);

  while (ptr)
  {
    printf("'%s'\n", ptr);
    ptr = strtok(NULL, delim);
  }

  printf("\n");
}

// Reads a Process Queue from an input file [def]
Queue *load_queue(char *path, int max)
{
  char str[max];
  FILE *fp = fopen(path, "r");

  if (!fp)
  {
    printf("Error al abrir '%s'", path);
    return 1;
  }

  while (fgets(str, max, fp))
  {
    Process *process = load_process(str);
  }

  fclose(fp);

  return 0;
}

// Writes the output file [def]
void dump(int n)
{
  ;
}
