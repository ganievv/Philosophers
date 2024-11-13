# Philosophers Project

## Overview

The Philosophers project demonstrates a concurrency problem inspired by the classic "Dining Philosophers" problem. The purpose of this project is to explore the basics of threading, process synchronization, mutexes, and semaphores.

## About the Project

This project simulates philosophers sitting at a round table, alternately eating, thinking, or sleeping, while using shared forks to eat. The goal is to ensure no philosopher starves, demonstrating synchronization techniques using threads and mutexes (or processes and semaphores for the bonus).

## How It Works

- **Philosophers** sit around a table with a bowl of spaghetti and a fork between each pair.
- **Actions**: A philosopher can think, eat, or sleep. Eating requires two forks.
- The simulation stops when a philosopher dies of starvation or when all philosophers have eaten a specified number of times.
- Philosophers do not communicate directly, and you must ensure no data races occur.

## Installation

Clone the repository:
   ```bash
   git clone https://github.com/ganievv/Philosophers.git
   ```
Change to the project directory:
   ```bash
   cd Philosophers
   ```

To compile the project, use the provided Makefile:
```bash
make
```

To clean up compiled files:
```bash
make clean
```

To completely clean and rebuild:
```bash
make re
```

## Usage

Run the program with the following syntax:
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

Example:
```bash
./philo 5 800 200 200
```
