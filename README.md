# Minishell

This project challenged us to make our own shell. So this project is a lightweight, reduced version of the Bash shell (a humbly little version of that) written in C. It provides a simple and minimalistic command-line interface for users to interact with the operating system. Developed in pair with @0xEDU.

## Features

- Simple command-line interface
- Command history
- Built-in commands: cd, pwd, export, unset, env, exit, echo
- Command execution with arguments
- Multiple command execution with pipes: |
- Redirecting operators: <, >, >> and <<
- Environment variable expansion: $
- Signal handling: CTRL-C, CTRL-D

## Getting Started

### Prerequisites

To compile and run Minishell, you'll need a C compiler and the GNU Readline library. The following instructions assume you are using a Unix-based system, such as Linux or macOS.

### Compilation

1. Clone the repository:

```bash
git clone https://github.com/Guiribei/my_shell.git
```

2. Change to the repository directory:

```bash
cd my_shell
```

3. Compile the project using the provided Makefile:

```bash
make
```

### Running Minishell

After successful compilation, you can run Minishell by executing the generated binary:

```bash
./minishell
```

You will be greeted with a colored command prompt, where you can start entering commands.

```diff
+minishell:~$
```

## Example Usage

Here's a quick example of what you can do with Minishell:


```
minishell:~/home/user/my_shell$ echo "Hello, World!"
Hello, World!
minishell:~/home/user/my_shell$ ls
includes  libft  Makefile  minishell  objects  sources
minishell:~/home/user/my_shell$ exit
```

### Limitations

Minishell is a reduced version of Bash, and as such, it does not support all features available in a full-featured shell. Some of the missing features include:
- Command separators as ; and &&
- Scripting capabilities
- Customization and extensibility
- Wildcards
