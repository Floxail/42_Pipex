# Pipex

*This project has been created as part of the 42 curriculum by flvejux.*

## Description

Pipex is a project that recreates the behavior of shell pipes in C. The program takes two commands and two files as arguments, executing the commands in sequence with a pipe between them, mimicking the shell pipe mechanism `< file1 cmd1 | cmd2 > file2`.

The goal is to understand and implement UNIX process management, file descriptors, and inter-process communication through pipes.

## Instructions

### Compilation

```bash
make
```

The Makefile includes the following rules:
- `make` or `make all`: Compile the project
- `make clean`: Remove object files
- `make fclean`: Remove object files and executable
- `make re`: Recompile the project from scratch
- `make bonus`: Compile the bonus version (if implemented)

### Usage

```bash
./pipex file1 cmd1 cmd2 file2
```

**Arguments:**
- `file1`: Input file
- `cmd1`: First shell command with its parameters
- `cmd2`: Second shell command with its parameters
- `file2`: Output file

**Example:**

```bash
./pipex infile "ls -l" "wc -l" outfile
```

This behaves like: `< infile ls -l | wc -l > outfile`

```bash
./pipex infile "grep a1" "wc -w" outfile
```

This behaves like: `< infile grep a1 | wc -w > outfile`

### Bonus Features

If implemented, the bonus version supports:

1. Multiple pipes:
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```
Equivalent to: `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`

2. Here-doc support:
```bash
./pipex here_doc LIMITER cmd cmd1 file
```
Equivalent to: `cmd << LIMITER | cmd1 >> file`

## Resources

### Documentation
- `man pipe`
- `man fork`
- `man execve`
- `man dup2`
- `man waitpid`
- `man access`
- [GitBook](https://42-cursus.gitbook.io/guide/2-rank-02/pipex)
- [Code Vault on YTB](https://www.youtube.com/watch?v=6xbLgZpOBi8)

### AI Usage

AI tools were used in the development of this project:
- Claude Code assisted in creating the Makefile structure
- Gemini provided guidance on project architecture and module organization
