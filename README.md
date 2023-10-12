# 0x16. C - Simple Shell

## Description

This is a simple UNIX command interpreter that replicates functionalities of the simple shell (sh). Additional functions are also included. This program was written entirely in C as a milestone project for Alx-Holberton School.

## Usage

After compilation, the resulting program can run stand-alone, either in interactive or non-interactive mode.

## Interactive Mode

In interactive mode, simply run the program and wait for the prompt to appear. From there, you can type commands freely, exiting with either the "exit" command or ctrl-D.

## Non-Interactive Mode

In non-interactive mode, echo your desired command and pipe it into the program like this:

echo "ls" | ./shell
In non-interactive mode, the program will exit after finishing your desired command(s).

This is the man page which contains all functions and descriptions of all the functions used in this Simple shell project. To access this page, Do:

## Features

1. DIsplay a prompt and wait for the user to type a command. A command-line always ends with a new line.
2. The prompt is displayed again each time a command has been executed.
3. The command lines are simple and also contain semicolons, pipes, redirections, and other advanced features.
4. The command line handle the “end of file” condition (Ctrl+D).
5. If an executable is not found the shell prints an error message and display the prompt again.

## Acknowledgements

This project was written as part of the curriculum of the ALX-SE programme by Holberton School. Holberton School is a campus-based full-stack software engineering program that prepares students for careers in the tech industry using project-based peer learning.
