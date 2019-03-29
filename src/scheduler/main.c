#include "../io/io.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void simulate(Queue *queue, int length, int quantum)
{
  Process *process;
  Burst *burst;
  int i;
  int t = 0;
  bool CPU_signal = false;
  bool CPU_available = true;
  int finished_count = 0;
  int pid_count = 0;

  // not all Process' are FINISHED
  while (finished_count != length)
  {
    printf("\nT = %d:\n", t);

    // cycle(queue);

    for (i = 0; i < length; i++)
    {
      process = cycle(queue);

      // Process is GHOST
      if (process->state == Ghost && process->t0 <= t)
      {
        if (!(process->pid))
        {
          pid_count++;
          process->pid = pid_count;
        }

        if (CPU_available)
        {
          process->stats->response_time = t - process->t0;
          process->stats->waiting_time += process->stats->response_time;
          process->state = Ready;

          printf("Process '%s' has been READY for %d seconds.\n", process->name, process->stats->response_time);
        }
      }

      // Process is READY
      if (process->state == Ready)
      {
        // no other Process is currently RUNNING
        if (CPU_available)
        {
          process->stats->cpu_count++;
          CPU_available = false;
          process->state = Running;

          printf("Process '%s' is now RUNNING.\n", process->name);
        }

        // another Process is currently RUNNING
        else
        {
          process->stats->waiting_time++;
        }
      }

      // Process is RUNNING
      if (process->state == Running)
      {
        burst = (process->bursts)[process->curr_burst];
        burst->runtime++;

        if (quantum)
        {
          process->CPU_time++;

          if (process->CPU_time == quantum)
          {
            process->stats->interruption_count++;
            process->CPU_time = 0;
            CPU_signal = true;
            process->state = Ready;

            printf("Process '%s' was INTERRUPTED after %d seconds of RUNNING.\n", process->name, burst->runtime);
          }
        }

        // current CPU Burst is done
        if (burst->duration == burst->runtime)
        {
          process->curr_burst++;
          CPU_signal = true;

          if (quantum)
          {
            process->CPU_time = 0;
          }

          // Process has more Bursts left, thus it's not over
          if (process->curr_burst != process->N)
          {
            process->state = Waiting;

            printf("Process '%s' is now WAITING after %d seconds of RUNNING.\n", process->name, burst->duration);
          }

          // Process has no Bursts left, thus it's over
          else
          {
            process->stats->turnaround_time = t - process->t0;

            finished_count++;
            process->state = Finished;

            printf("Process '%s' has FINISHED after %d seconds of RUNNING.\n", process->name, burst->duration);
          }
        }

        // current CPU Burst is not done yet
        else
        {
          printf("Process '%s' has been RUNNING for %d seconds.\n", process->name, burst->runtime);
        }
      }

      // Process is WAITING
      else if (process->state == Waiting)
      {
        burst = (process->bursts)[process->curr_burst];
        burst->runtime++;

        process->stats->waiting_time++;

        // current I/O Burst is done
        if (burst->duration == burst->runtime)
        {
          process->curr_burst++;
          process->state = Ready;

          printf("Process '%s' is now READY after %d seconds of WAITING.\n", process->name, burst->duration);
        }

        // current I/O Burst is not done yet
        else
        {
          printf("Process '%s' has been WAITING for %d seconds.\n", process->name, burst->runtime);
        }
      }
    }

    if (CPU_signal)
    {
      CPU_available = true;
      CPU_signal = false;
    }

    t++;
  }
}

int main(int argc, char **argv)
{

  printf("\nLOADING PROCESSES...\n");
  Queue *queue = load_queue(argv[1], 1024);
  if (!queue)
  {
    return 1;
  }

  print_queue(queue);
  Queue *sorted = priority_sort(queue);

  int quantum;
  if (argv[3][0] == 'p')
  {
    quantum = 0;
  }
  else if (argv[3][0] == 'n')
  {
    quantum = argc > 4 ? atoi(argv[4]) : 3;
  }

  simulate(sorted, sorted->length, quantum);

  printf("\n\n");

  dump_results(sorted, queue, argv[2]);

  free_queue(queue);

  Node *node = sorted->head;
  Node *aux_node;
  while (node)
  {
    aux_node = node->next;
    free(node);
    node = aux_node;
  }
  free(sorted);

  return 0;
}
