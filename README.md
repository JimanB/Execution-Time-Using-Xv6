# xv6 Command Execution Time Measurement

## Overview
This project implements a user program `exectime.c` for the xv6 operating system that measures and displays the real time (clock time) spent executing shell commands. The program uses xv6 system calls to track command execution duration and displays both start and completion times in terms of ticks.

## Features
- Measures real-time execution duration of shell commands
- Displays start time and completion time in ticks
- Supports variable number of command line arguments
- Uses xv6 system calls: `uptime`, `fork`, `exec`, `wait`
- Includes comprehensive error handling

## Requirements
- The program must run within xv6 environment
- Only the Makefile can be modified in xv6
- No need to handle composite shell commands (like pipes)
- Variable number of command line arguments support

## System Calls Used
- **uptime()**: Returns the number of ticks since system boot
- **fork()**: Creates a new process
- **exec()**: Executes a specified program
- **wait()**: Waits for a child process to exit

## Implementation Details

The program works as follows:
1. Validates command line arguments and shows usage if no command provided
2. Gets the start time using `uptime()` and prints it
3. Forks a new process
4. In the child process: executes the specified command using `exec()`
5. In the parent process: waits for the child to complete using `wait()`
6. Gets the completion time using `uptime()` and prints it
7. The execution time can be calculated as the difference between end and start ticks

## Installation & Usage

### 1. Add to xv6
Copy `exectime.c` to your xv6 user programs directory and modify the `Makefile` to include it in the compilation by adding `_exectime\` to the `UPROGS` section.

### 2. Compile and Run
```bash
make
make qemu
```

### 3. Usage Examples
```bash
exectime ls
exectime echo "Hello World"
exectime cat README
```

### 4. Sample Output
```
$ exectime ls
uptime: 1355
.              1 1 1024
..             1 1 1024
README         2 2 2395
cat            2 3 41532
# ... (file listing continues)
exectime       2 21 40680
uptime: 1357
$
```

**Note:** The execution time is calculated as `1357 - 1355 = 2 ticks` (shown in the sample output).

## Code Structure
The implementation includes:
- Proper error checking for all system calls
- Usage message when no command is provided
- Fork failure handling
- Exec failure handling with descriptive error messages
- Clean process management with proper waiting

## Error Handling
- Displays "usage: exectime command [args...]" if no command provided
- Handles fork failures with "exectime: fork failed"
- Handles exec failures with "exectime: exec [command] failed"
- Uses appropriate file descriptors (1 for stdout, 2 for stderr)

## Limitations
- Does not handle composite commands with pipes (`|`)
- Does not handle redirections (`>`, `<`)
- Time measurement includes process creation overhead
- Output shows individual uptime values rather than calculated duration (user calculates difference)

## Notes
- The tick count represents the number of timer interrupts since boot
- The program prints start and end uptime values separately
- Execution duration is calculated as `end_ticks - start_ticks`
- Make sure to add `exectime` to the `UPROGS` in xv6's Makefile

## Files Included
- `exectime.c` - Main implementation file
- `Makefile` - Modified xv6 Makefile (ensure `_exectime\` is added to `UPROGS`)
