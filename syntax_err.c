#include "shell.h"

/**
 * rep_char - counts the repetitions of a char
 *
 * @in: input strings
 * @idx: index
 * Return: repetitions
 */
int rep_char(char *in, int idx)
{
	if (*(in - 1) == *in)
		return (rep_char(in - 1, idx + 1));

	return (idx);
}

/**
 * err_sep_op - finds syntax errors
 *
 * @in: input string
 * @idx: index
 * @lst: last char read
 * Return: index of error. 0 when there are no
 * errors
 */
int err_sep_op(char *in, int idx, char lst)
{
	int ct;

	ct = 0;
	if (*in == '\0')
		return (0);

	if (*in == ' ' || *in == '\t')
		return (err_sep_op(in + 1, idx + 1, lst));

	if (*in == ';')
		if (lst == '|' || lst == '&' || lst == ';')
			return (idx);

	if (*in == '|')
	{
		if (lst == ';' || lst == '&')
			return (idx);

		if (lst == '|')
		{
			ct = rep_char(in, 0);
			if (ct == 0 || ct > 1)
				return (idx);
		}
	}

	if (*in == '&')
	{
		if (lst == ';' || lst == '|')
			return (idx);

		if (lst == '&')
		{
			ct = rep_char(in, 0);
			if (ct == 0 || ct > 1)
				return (idx);
		}
	}

	return (err_sep_op(in + 1, idx + 1, *in));
}

/**
 * first_char - finds index of the first character
 *
 * @in: input strings
 * @idx: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *in, int *idx)
{

	for (*idx = 0; in[*idx]; *idx += 1)
	{
		if (in[*idx] == ' ' || in[*idx] == '\t')
			continue;

		if (in[*idx] == ';' || in[*idx] == '|' || in[*idx] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_err - prints when a syntax error is found
 *
 * @datashell: data structure
 * @in: input string
 * @idx: index of the error
 * @bool: to control message error
 * Return: no return
 */
void print_syntax_err(dt_shell *datashell, char *in, int idx, int bool)
{
	char *m, *m2, *m3, *err, *counter;
	int length;

	if (in[idx] == ';')
	{
		if (bool == 0)
			m = (in[idx + 1] == ';' ? ";;" : ";");
		else
			m = (in[idx - 1] == ';' ? ";;" : ";");
	}

	if (in[idx] == '|')
		m = (in[idx + 1] == '|' ? "||" : "|");

	if (in[idx] == '&')
		m = (in[idx + 1] == '&' ? "&&" : "&");

	m2 = ": Syntax error: \"";
	m3 = "\" unexpected\n";
	counter = _itoa(datashell->line_ct);
	length = str_len(datashell->av[0]) + str_len(counter);
	length += str_len(m) + str_len(m2) + str_len(m3) + 2;

	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(counter);
		return;
	}
	str_cpy(err, datashell->av[0]);
	str_cat(err, ": ");
	str_cat(err, counter);
	str_cat(err, m2);
	str_cat(err, m);
	str_cat(err, m3);
	str_cat(err, "\0");

	write(STDERR_FILENO, err, length);
	free(err);
	free(counter);
}

/**
 * check_syntax_err - intermediate function to
 * find and print a syntax error
 *
 * @datashell: data structure
 * @in: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_err(dt_shell *datashell, char *in)
{
	int bgn = 0;
	int _char = 0;
	int j = 0;

	_char = first_char(in, &bgn);
	if (_char == -1)
	{
		print_syntax_err(datashell, in, bgn, 0);
		return (1);
	}

	j = err_sep_op(in + bgn, 0, *(in + bgn));
	if (j != 0)
	{
		print_syntax_err(datashell, in, bgn + j, 1);
		return (1);
	}

	return (0);
}
