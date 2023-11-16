# OS Scheduler implementation in C

## Overview

This repository contains the source code for an operating system (Unix-like) scheduler implemented in C.

## Files and structure

The project is organized into several modules:

1. `io`
   
Contains the input/output functionality for reading and writing process data. Implements functions to load processes from an input file, dump statistics to an output file, and read process queues.

2.`process`

Defines the structures for bursts and processes, and defines functions to initialize, free, and manipulate them.

3. `queue`

Implements a basic queue data structure and associated operations, such as adding, popping, cycling, and sorting processes.

4. `stats`

Manages the statistics for each process. Implements the statistics structure and a function to initialize new process statistics.
