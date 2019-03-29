#include "../io/io.h"

#include <stdio.h>
#include <stdbool.h>

void sim_nonpreemptive(Queue *queue, int length)
{
  Process *process;
  Burst *burst;
  int i;
  int t = 0;
  bool CPU_available = true;
  int finished_count = 0;

  // not all Process' are FINISHED
  while (finished_count != length)
  {
    printf("\nT = %d:\n", t);

    for (i = 0; i < length; i++)
    {
      process = cycle(queue);

      // Process is GHOST
      if (process->state == Ghost && process->t0 >= t && CPU_available)
      {
        process->stats->response_time = t - process->t0;
        process->stats->waiting_time += process->stats->response_time;
        process->curr_burst = 0;
        process->state = Ready;

        printf("Process '%s' is READY.\n", process->name);
      }

      // Process is READY
      if (process->state == Ready && CPU_available)
      {
        process->state = Running;
        process->stats->cpu_count++;
        CPU_available = false;

        printf("Process '%s' is RUNNING.\n", process->name);
      }

      // Process is RUNNING
      if (process->state == Running)
      {
        burst = (process->bursts)[process->curr_burst];

        // current CPU Burst is done
        if (burst->duration == burst->runtime)
        {
          process->curr_burst++;
          CPU_available = true;

          // Process has more Bursts left, thus it's not over
          if (process->curr_burst < process->N)
          {
            process->state = Waiting;

            printf("Process '%s' is WAITING.\n", process->name);
          }

          // Process has no Bursts left, thus it's over
          else
          {
            process->state = Finished;
            finished_count++;

            printf("Process '%s' is FINISHED.\n", process->name);
          }
        }

        // current CPU Burst is not done yet
        else
        {
          burst->runtime++;
          process->stats->turnaround_time++;

          printf("Process '%s' is still RUNNING.\n", process->name);
        }
      }

      // Process is WAITING
      else if (process->state == Waiting)
      {
        burst = (process->bursts)[process->curr_burst];

        // current I/O Burst is done
        if (burst->duration == burst->runtime)
        {
          process->curr_burst++;
          process->state = Ready;

          printf("Process '%s' is READY.\n", process->name);
        }

        // current I/O Burst is not done yet
        else
        {
          burst->runtime++;
          process->stats->turnaround_time++;
          process->stats->waiting_time++;

          printf("Process '%s' is still WAITING.\n", process->name);
        }
      }
    }

    t++;
  }
}

void sim_preemptive(Queue *queue, int length)
{
}

int main()
{
  Queue *queue = load_queue("data/test1.txt", 1024);
  if (!queue)
  {
    return 1;
  }

  // NON-PREEMPTIVE
  sim_nonpreemptive(queue, queue->length);

  // PREEMPTIVE
  // sim_preemptive(queue, queue->length);

  free_queue(queue);

  return 0;
}
