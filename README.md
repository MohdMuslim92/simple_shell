# Simple Shell

This is a simple shell program written in C programming language. It supports basic shell functionality such as executing commands and managing processes. This project is contributed by Mohammed Saeed and Mojtaba Babiker.

# Getting Started
To use the shell program, you can clone the repository to your local machine:

```console
git clone https://github.com/MohdMuslim92/simple_shell.git   
```
Then compile the program using GCC compiler:
```console
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh   
```
Finally, run the program:

```console
./hsh   
```

# Features
* Supports executing commands with arguments
* Supports background processes
* Supports basic shell built-in commands such as cd and exit   

# Usage
Here are some examples of how to use the shell program:

```console
$ ls   
```
This will execute the ls command and list the files in the current directory.

```console
$ ls -l /home/user   
```
This will execute the ls command with the -l option and list the files in the /home/user directory.

```console
$ cd /home/user   
```
This will change the current directory to /home/user.

# Contributions
This project is a collaborative effort by Mohammed Saeed and Mojtaba Babiker. If you find any bugs or have suggestions for improvement, please create an issue or submit a pull request.

# License
This project is licensed under the ALX License - see the LICENSE file for details.
