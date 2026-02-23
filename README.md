# Philosophers

> A multithreading and synchronization project from 42 School based on the classic **Dining Philosophers Problem**.

## Overview

This project is an implementation of the famous **Dining Philosophers Problem**, designed to teach:

- Thread creation and management
- Mutexes and synchronization
- Avoiding race conditions
- Preventing deadlocks
- Precise timing in concurrent systems

Each philosopher is represented by a thread. They alternate between:

- Eating  
- Sleeping  
- Thinking  

This project ensures safe and deterministic behavior using **POSIX threads (`pthread`) and mutexes**.

---

## Program Arguments

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parameters

| Argument | Description |
|--------|-------------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time (ms) before a philosopher dies without eating |
| `time_to_eat` | Time (ms) spent eating |
| `time_to_sleep` | Time (ms) spent sleeping |
| `number_of_times_each_philosopher_must_eat` | (Optional) Simulation stops when all philosophers eat this many times |

---

## Threading Model

- Each philosopher runs in its **own thread**
- Each fork is protected by a **mutex**
- Printing is protected to avoid output corruption
- A monitor checks:
  - Death conditions
  - Meal completion (if required)

---

## Synchronization Strategy

- Forks are protected with mutexes
- Deadlock prevention using fork ordering or odd/even strategy
- Shared state protected:
  - Last meal time
  - Meal count
  - Death flag
  - Printing

---

## Timing

- Uses `gettimeofday()` for timestamps
- Custom sleep for accurate delays
- All timestamps are relative to simulation start

Example output:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

---

## Compilation

```bash
make
```

Available rules:

```bash
make clean
make fclean
make re
```

Compiled with:

```bash
cc -Wall -Wextra -Werror -pthread
```

---

## Example

```bash
./philo 5 800 200 200
```

---

## Edge Cases Handled

- Single philosopher
- Tight timing values
- Thread cleanup
- No memory leaks
- No data races

---

## Project Structure

```
.
├── Makefile
├── philo.h
├── main.c
├── init.c
├── actions.c
├── monitor.c
├── utils.c
└── free.c
```

---

## What I Learned

- Multithreading fundamentals
- Mutex-based synchronization
- Deadlock prevention
- Race condition handling
- Time-sensitive simulations


