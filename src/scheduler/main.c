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

    for (i = 0; i < length; i++)
    {
      process = cycle(queue);
      burst = (process->bursts)[process->curr_burst];

      // Process is GHOST
      if (process->state == Ghost && process->t0 >= t && CPU_available)
      {
        process->stats->response_time = t - process->t0;
        process->stats->waiting_time += process->stats->response_time;
        process->curr_burst = 0;
        process->state = Ready;
      }

      // Process is READY
      if (process->state == Ready && CPU_available)
      {
        process->state = Running;
        process->stats->cpu_count++;
      }

      // Process is RUNNING
      if (process->state == Running)
      {

        // current CPU Burst is done
        if (burst->duration == burst->runtime)
        {
          process->curr_burst++;

          // Process has more Bursts left, thus it's not over
          if (process->curr_burst < process->N)
          {
            process->state = Waiting;
          }

          // Process has no Bursts left, thus it's over
          else
          {
            process->state = Finished;
            finished_count++;
          }
        }

        // current CPU Burst is not done yet
        else
        {
          burst->runtime++;
          process->stats->turnaround_time++;
        }
      }

      // Process is WAITING
      else if (process->state == Waiting)
      {

        // current I/O Burst is done
        if (burst->duration == burst->runtime)
        {
          process->curr_burst++;
          process->state = Ready;
        }

        // current I/O Burst is not done yet
        else
        {
          burst->runtime++;
          process->stats->turnaround_time++;
          process->stats->waiting_time++;
        }
      }
    }

    t++;
  }
}

void sim_preemptive(Queue *queue)
{
}

int main()
{
  Queue *queue = load_queue("data/test1.txt", 1024);
  if (!queue)
  {
    return 1;
  }

  return 0;
}
