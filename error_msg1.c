#include "shell.h"

/**
 * str_cat_cd - function that concatenates the message for cd error
 *
 * @datashell: data relevant (directory)
 * @m: message to print
 * @err: output message
 * @ver_str: counter lines
 * Return: error message
 */
char *str_cat_cd(dt_shell *datashell, char *m, char *err, char *ver_str)
{
	char *illegal_flag;

	str_cpy(err, datashell->av[0]);
	str_cat(err, ": ");
	str_cat(err, ver_str);
	str_cat(err, ": ");
	str_cat(err, datashell->args[0]);
	str_cat(err, m);
	if (datashell->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datashell->args[1][1];
		illegal_flag[2] = '\0';
		str_cat(err, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		str_cat(err, datashell->args[1]);
	}

	str_cat(err, "\n");
	str_cat(err, "\0");
	return (err);
}

/**
 * err_get_cd - error message for cd command in get_cd
 * @datashell: data relevant (directory)
 * Return: Error message
 */
char *err_get_cd(dt_shell *datashell)
{
	int len, length_id;
	char *err, *ver_str, *m;

	ver_str = _itoa(datashell->line_ct);
	if (datashell->args[1][0] == '-')
	{
		m = ": Illegal option ";
		length_id = 2;
	}
	else
	{
		m = ": can't cd to ";
		length_id = str_len(datashell->args[1]);
	}

	len = str_len(datashell->av[0]) + str_len(datashell->args[0]);
	len += str_len(ver_str) + str_len(m) + length_id + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}

	err = str_cat_cd(datashell, m, err, ver_str);

	free(ver_str);

	return (err);
}

/**
 * err_not_found - generic error message for command not found
 * @datashell: data relevant (counter, arguments)
 * Return: Error message
 */
char *err_not_found(dt_shell *datashell)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = _itoa(datashell->line_ct);
	len = str_len(datashell->av[0]) + str_len(ver_str);
	len += str_len(datashell->args[0]) + 16;
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
	str_cat(err, ": not found\n");
	str_cat(err, "\0");
	free(ver_str);
	return (err);
}

/**
 * err_exit_sh - generic error message for exit in get_exit
 * @datashell: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *err_exit_sh(dt_shell *datashell)
{
	int len;
	char *err;
	char *ver_str;

	ver_str = _itoa(datashell->line_ct);
	len = str_len(datashell->av[0]) + str_len(ver_str);
	len += str_len(datashell->args[0]) + str_len(datashell->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(ver_str);
		return (NULL);
	}
	str_cpy(err, datashell->av[0]);
	str_cat(err, ": ");
	str_cat(err, ver_str);
	str_cat(err, ": ");
	str_cat(err, datashell->args[0]);
	str_cat(err, ": Illegal number: ");
	str_cat(err, datashell->args[1]);
	str_cat(err, "\n\0");
	free(ver_str);

	return (err);
}
