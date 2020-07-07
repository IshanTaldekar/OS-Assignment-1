# Operating Systems - Programming Assignment 1

## Problem Statement
The objectives of this lab were to familiarize the students with basic concepts of UNIX process execution and creation and to learn the basics of the exec/fork system calls and introductory C programming in Linux. We were required to write a program using the “execvp” command to execute commands given from the command line. In addition to this, we needed to make use of the fork system call to create a child to run the execvp command on, while the parent monitored the child’s resource usage.

## Implementation
I implemented my code on a Linux machine running Ubuntu 18.04 and tested it on the terminal. The machine has GCC version 7.4.0.  My code makes use of a switch statement, after having called fork(), to get the parent and the child to execute two distinct snippets of code. The child processes the arguments parsed in through the terminal as the parameters for an execvp call, which terminates the current process and runs this set of arguments. On the other hand, the parent waits for the child process to terminate. After the child process exits, the parent records the time the child spent in user mode and kernel mode and reports it to the user.  
