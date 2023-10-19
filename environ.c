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
