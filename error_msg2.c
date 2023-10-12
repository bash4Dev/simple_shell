#include "shell.h"

/**
 * env_error - error message for env in get_env.
 * @datashell: data relevant (counter, arguments)
 * Return: error message.
 */
char *env_error(dt_shell *datashell)
{
	int len;
	char *err;
	char *ver_str;
	char *m;

	ver_str = _itoa(datashell->line_ct);
	m = ": Unable to add/remove from environment\n";
	len = str_len(datashell->av[0]) + str_len(ver_str);
	len += str_len(datashell->args[0]) + str_len(m) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}

	str_cpy(err, datashell->av[0]);
	str_cat(err, ": ");
	str_cat(err, ver_str);
	str_cat(err, ": ");
	str_cat(err, datashell->args[0]);
	str_cat(err, m);
	str_cat(err, "\0");
	free(ver_str);

	return (err);
}
/**
 * path_err126 - error message for path and failure denied permission.
 * @datashell: data relevant (counter, arguments).
 *
 * Return: error string.
 */
char *path_err126(dt_shell *datashell)
{
	int len;
	char *ver_str;
	char *err;

	ver_str = _itoa(datashell->line_ct);
	len = str_len(datashell->av[0]) + str_len(ver_str);
	len += str_len(datashell->args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(ver_str);
		return (NULL);
	}
	str_cpy(err, datashell->av[0]);
	str_cat(err, ": ");
	str_cat(err, ver_str);
	str_cat(err, ": ");
	str_cat(err, datashell->args[0]);
	str_cat(err, ": Permission denied\n");
	str_cat(err, "\0");
	free(ver_str);
	return (err);
}
