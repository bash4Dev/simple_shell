#include "shell.h"

/**
 * free_data - frees data structure
 *
 * @datashell: data structure
 * Return: no return
 */
void free_data(dt_shell *datashell)
{
	unsigned int k;

	for (k = 0; datashell->environ[k]; k++)
	{
		free(datashell->environ[k]);
	}

	free(datashell->environ);
	free(datashell->sh_pid);
}

/**
 * set_data - Initialize data structure
 *
 * @datashell: data structure
 * @arg_v: argument vector
 * Return: no return
 */
void set_data(dt_shell *datashell, char **arg_v)
{
	unsigned int i;

	datashell->av = arg_v;
	datashell->input = NULL;
	datashell->args = NULL;
	datashell->lst_sts = 0;
	datashell->line_ct = 1;

	for (i = 0; environ[i]; i++)
		;
	datashell->environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datashell->environ[i] = str_dup(environ[i]);
	}

	datashell->environ[i] = NULL;
	datashell->sh_pid = _itoa(getpid());
}

/**
 * get_sigint - Handle the crtl + c call in prompt
 * @s: Signal handler
 */
void get_sigint(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n~$ ", 5);
}

/**
 * main - Entry point
 *
 * @arg_c: argument count
 * @arg_v: argument vector
 *
 * Return: 0 on success.
 */
int main(int arg_c, char **arg_v)
{
	dt_shell datashell;
	(void) arg_c;

	signal(SIGINT, get_sigint);
	set_data(&datashell, arg_v);
	sh_loop(&datashell);
	free_data(&datashell);
	if (datashell.lst_sts < 0)
		return (255);
	return (datashell.lst_sts);
}
