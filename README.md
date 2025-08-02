# Linux-Based Process Manager (C++ CLI Tool)

This is a lightweight Linux-based command-line tool written in C++ for **monitoring and managing system processes**. It uses core Linux system programming concepts like the `/proc` filesystem, signals, threading, and inter-process communication (IPC).

## Features

- **List running processes** using `/proc`
- **Display detailed process information** by PID
- **Kill a process** using its PID
- **Live process usage monitor** sorted by CPU usage (refreshes every 2 seconds)
- **Top 10 memory-consuming processes** using `ps`, `pipe`, and `fork`

## File Overview

- `main.cpp`: Complete implementation of the CLI tool with all options
- Uses:
  - `/proc` filesystem
  - `fork`, `exec`, `pipe`, `kill`
  - POSIX threads (`pthread`)
  - Standard Linux commands for process metrics

## Usage

### Compile the program
```bash
g++ main.cpp -o proc_manager -lpthread
```

### Run it
```bash
./proc_manager
```

## Menu Options

```
[1] List Processes
[2] Show Process Details
[3] Kill Process
[4] Monitor Usage
[5] Show Top Memory-Consuming Processes
[6] Exit
```

- **List Processes**: Shows all numeric PIDs and their process names.
- **Show Process Details**: Displays all `/proc/<pid>/status` info.
- **Kill Process**: Sends `SIGKILL` to the entered PID.
- **Monitor Usage**: Launches a live dashboard of top CPU consumers.
- **Top Memory-Consuming Processes**: Uses `fork + pipe + exec` to show the top 10 memory-heavy processes.

## Technologies Used

- **C++**
- **Linux System Programming**
  - `fork`, `pipe`, `exec`, `kill`, `/proc`
- **Multithreading** using `pthread`
- **IPC and signals**
- **Basic Shell commands** like `ps`, `head`, `sort`

---
