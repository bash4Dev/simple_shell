#include "shell.h"

/**
 * help_env - Help information for the builtin env
 * Return: no return
 */
void help_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Print the enviroment of the shell.\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * help_setenv - Help information for the builtin setenv
 * Return: no return
 */
void help_setenv(void)
{
	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, str_len(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, str_len(help));
	help = "Add a new definition to the environment\n";
	write(STDOUT_FILENO, help, str_len(help));
}

/**
 * help_unsetenv - Help information for the builtin unsetenv
 * Return: no return
 */
void help_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, str_len(help));
	help = "Remove an entry completely from the environment\n";
	write(STDOUT_FILENO, help, str_len(help));
}
