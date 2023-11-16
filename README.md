# OS Scheduler implementation in C

## Overview

This repository contains the source code for an operating system (Unix-like) scheduler implemented in C.

## Files and structure

The project is organized into several modules:

1. `io`
   
Contains the input/output functionality for reading and writing process data. Implements functions to load processes from an input file, dump statistics to an output file, and read process queues.

2. `process`

Defines the structures for bursts and processes, and defines functions to initialize, free, and manipulate them.

3. `queue`

Implements a basic queue data structure and associated operations, such as adding, popping, cycling, and sorting processes.

4. `stats`

Manages the statistics for each process. Implements the statistics structure and a function to initialize new process statistics.

## Example usage

After compiling the program to an executable named `scheduler`:

```bash
./scheduler input.txt output.txt
```

Replace `input.txt` with your input file containing process data and observe the scheduler's output in `output.txt`.

## Input file format

The input file for the OS scheduler follows a specific format to define the processes and their characteristics. Each line represents a single process, and spaces separate the fields. The format is as follows:

```txt
[ProcessName] [Priority] [StartTime] [BurstCount] [Burst1] [Burst2] ... [BurstN]
```

- `ProcessName`: A string representing the name of the process.
- `Priority`: An integer indicating the priority of the process.
- `StartTime`: An integer specifying the process's start time.
- `BurstCount`: An integer indicating the number of bursts for the process.
- `Burst1`, `Burst2`, ..., `BurstN`: Integers representing the durations of alternating CPU and IO bursts. The total number of bursts is twice the value of BurstCount.

Example:

```txt
Process1 1 0 3 10 5 8 2 6
Process2 2 1 2 7 4 9
```

Please ensure your input files follow these formats to use the OS scheduler effectively.

## Output file format

The OS scheduler's output file contains each process's statistics after execution. Each line corresponds to a process and includes the following fields:

```txt
[ProcessName],[CPUCount],[InterruptionCount],[TurnaroundTime],[ResponseTime],[WaitingTime]
```

- `ProcessName`: The name of the process.
- `CPUCount`: The total count of CPU bursts executed.
- `InterruptionCount`: The count of times the process was interrupted.
- `TurnaroundTime`: The total time taken by the process from start to finish.
- `ResponseTime`: The time taken for the process to start running.
- `WaitingTime`: The total time the process spent waiting in the ready queue.

Example:

```txt
Process1,3,2,24,8,10
Process2,2,1,20,7,9
```
