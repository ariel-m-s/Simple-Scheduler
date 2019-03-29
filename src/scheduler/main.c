#include "../io/io.h"

#include <stdio.h>
#include <stdbool.h>

void sim_nonpreemptive(Queue *queue, int length)
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

        process->stats->turnaround_time++;

        // current CPU Burst is done
        if (burst->duration == burst->runtime)
        {
          process->curr_burst++;
          CPU_signal = true;

          // Process has more Bursts left, thus it's not over
          if (process->curr_burst != process->N)
          {
            process->state = Waiting;

            printf("Process '%s' is now WAITING after %d seconds of RUNNING.\n", process->name, burst->duration);
          }

          // Process has no Bursts left, thus it's over
          else
          {
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
        process->stats->turnaround_time++;

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
  // print_queue(queue);
  priority_sort(queue);
  // print_queue(queue);
  sim_nonpreemptive(queue, queue->length);

  Node *node = queue->head;
  while(node)
  {
    print_stats(node->value);
    node = node->next;
  }

  // PREEMPTIVE
  // print_queue(queue);
  // sim_preemptive(queue, queue->length);

  free_queue(queue);

  return 0;
}
