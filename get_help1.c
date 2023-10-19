#include "shell.h"

/**
 * _help - Help information for the builtin help.
 * Return: no return
 */
void _help(void)
{
        char *h = "help: help [-dms] [pattern ...]\n";

        write(STDOUT_FILENO, h, str_len(h));
        h = "\tDisplay information about builtin commands.\n ";
        write(STDOUT_FILENO, h, str_len(h));
        h = "Displays brief summaries of builtin commands.\n";
        write(STDOUT_FILENO, h, str_len(h));
}

/**
 * help_alias - Help infor for the builtin alias.
 * Return: no return
 */
void help_alias(void)
{
        char *hp = "alias: alias [-p] [name[=value]...]\n";

        write(STDOUT_FILENO, hp, str_len(hp));
        hp = "\tDefine or display aliases.\n ";
        write(STDOUT_FILENO, hp, str_len(hp));
}

/**
 * help_cd - Help infor for the builtin alias.
 * Return: no return
 */
void help_cd(void)
{
        char *h = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

        write(STDOUT_FILENO, h, str_len(h));
        h = "\tChange the shell working directory.\n ";
        write(STDOUT_FILENO, h, str_len(h));
}

/**
 * help_gen - Entry point for help infor for the help builtin
 * Return: no return
 */
void help_gen(void)
{
	char *help = "^-^ bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "These commands are defined internally.Type
		'help' to see the list";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Type 'help name' to find out more about the function 'name'.
		\n\n ";
	write(STDOUT_FILENO, help, str_len(help));
	help = " alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "[dir]\nexit: exit [n]\n  env:
		env [option] [name=value] [command ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "[args]]\n  setenv: setenv [variable] [value]\n  unsetenv: ";
	write(STDOUT_FILENO, help, str_len(help));
	help = "unsetenv [variable]\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * help_exit - Help infor fot the builint exit
 * Return: no return
 */
void help_exit(void)
{
	char *help = "exit: exit [n]\n Exit shell.\n";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Exits the shell with a status of N. If N is ommited, the exit";
	write(STDOUT_FILENO, help, str_len(help));
	help = "statusis that of the last command executed\n";
	write(STDOUT_FILENO, help, str_len(help));
}
