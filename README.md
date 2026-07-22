# 🐧 ScriptWarrior Shell

## Overview

ScriptWarrior Shell is a Mini Linux Shell developed in C that simulates the behavior of a Unix/Linux command-line interpreter. It supports command execution, process scheduling, and automation tasks, making it a useful educational project for learning Operating System concepts.

---

## Features

- Execute Linux shell commands
- First Come First Serve (FCFS) Scheduling
- Round Robin (RR) Scheduling
- Automation commands
- Interactive command-line interface
- Modular C implementation
- Built using Makefile

---

## Technologies Used

- C Programming
- GCC Compiler
- Makefile
- Linux System Calls

---
## Requirements

- Linux or macOS
- GCC Compiler
- Make
- Python 3.x (only if using the optional GUI)

---

## Default Login Credentials

The shell requires authentication before use.

| Username | Password |
|----------|----------|
| `admin` | `1234` |

> These are the default demonstration credentials for educational purposes.

---

## Project Structure

```
scriptwarrior_shell
├── src
│   ├── main.c
│   ├── commands.c
│   ├── commands.h
│   ├── scheduler.c
│   ├── scheduler.h
│   ├── utils.c
│   ├── utils.h
│   └── scriptwarrior_shell.h
├── Makefile
└── README.md
```

---

## Build

Compile the project using:

```bash
make
```

---

## Run

Start the shell using:

```bash
./scriptwarrior_shell
```

---

## Supported Commands

ScriptWarrior Shell executes standard Linux commands using the `execvp()` system call.

### Examples

Display current directory:

```bash
pwd
```

List files:

```bash
ls
ls -l
```

Create a directory:

```bash
mkdir test
```

Navigate to a directory:

```bash
cd directory_name
```

Display a file:

```bash
cat file.txt
```

Copy files:

```bash
cp file1.txt file2.txt
```

Move or rename files:

```bash
mv file1.txt file2.txt
```

Remove files:

```bash
rm file.txt
```

Print text:

```bash
echo Hello World
```

Clear the terminal:

```bash
clear
```

> **Note:** Any command available on the host operating system can be executed through the shell.

### Custom Commands

The shell also provides custom educational commands:

#### First Come First Serve (FCFS)

```bash
fcfs command1 command2 command3
```

#### Round Robin Scheduling

```bash
rr 2 command1 command2 command3
```

#### Automation

```bash
automate
```

Runs predefined automation tasks.

#### Exit

```bash
exit
```

Closes the shell.
---

## Learning Objectives

This project demonstrates:

- Shell Programming
- Process Scheduling
- Operating System Concepts
- Command Execution
- Modular Programming in C

---

## Author

**Rahul Singh**

B.Tech CSE
