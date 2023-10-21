#include "shell.h"

/**
 * _env - prints the evironment variables
 *
 * @datashell: data relevant.
 * Return: 1 on success.
 */
int _env(dt_shell *datashell)
{
	int i, j;

	for (i = 0; datashell->environ[i]; i++)
	{
		for (j = 0; datashell->environ[i][j]; j++)
			;
		write(STDOUT_FILENO, datashell->environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	datashell->lst_sts = 0;

	return (1);
}

/**
 * cmp_env - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}
	return (i + 1);
}

/**
 * get_env - get an environment variable
 * @name: name of the environment variable
 * @environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *get_env(const char *name, char **environ)
{
	char *ptr_env;
	int i, move;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	move = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; environ[i]; i++)
	{
		/* If name and env are equal */
		move = cmp_env(environ[i], name);
		if (move)
		{
			ptr_env = environ[i];
			break;
		}
	}
	return (ptr_env + move);
}
