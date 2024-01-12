# Pipex Project

## Overview
The Pipex project is an implementation of a simple yet powerful concept used in shell programming: the pipe. This program simulates the behavior of a pipe (`|`) and redirection (`>`) operators in a Unix shell. It takes commands as arguments and executes them in a pipeline fashion, where the output of one command serves as the input to the next.

### Features
- **Standard Mode**: Execute a series of commands, piping the output of one into the input of another.
- **Here-Doc Mode**: A feature similar to the Unix here-document, allowing input to be entered directly from the command line until a specified delimiter is encountered.

## Getting Started

### Prerequisites
- A Unix-like operating system (Linux/MacOS)
- GCC compiler

### Installation
1. Clone the repository:
   ```
   git clone https://your-repository-link/pipex.git
   ```
2. Change to the project directory:
   ```
   cd pipex
   ```
3. Compile the project:
   ```
   make all
   ```

## Usage

### Standard Mode
Execute the program with the input file, a list of commands, and the output file:
```
./pipex infile "cmd1" "cmd2" ... "cmdN" outfile
```
Example:
```
./pipex infile "grep foo" "wc -l" outfile
```
Equivalent shell command:
```
< infile grep foo | wc -l > outfile
```

### Here-Doc Mode
To use the here-doc feature, start with `here_doc` followed by the delimiter, then the list of commands, and the output file:
```
./pipex here_doc DELIMITER "cmd1" "cmd2" ... "cmdN" outfile
```
Example:
```
./pipex here_doc END "grep foo" "wc -l" outfile
```
Enter your input text after running the command. To terminate the input, type the delimiter `END`.

Equivalent shell command:
```
cat << END | grep foo | wc -l >> outfile
```

## Acknowledgments
- 42 School for the project guidelines.
