#include "shell.h"

/**
 * swap_chars - swaps | and & for non-printed chars
 *
 * @in_st: input string
 * @bool: type of swap
 * Return: swapped strings
 */
char *swap_chars(char *in_st, int bool)
{
	int j;

	if (bool == 0)
	{
		for (j = 0; in_st[j]; j++)
		{
			if (in_st[j] == '|')
			{
				if (in_st[j + 1] != '|')
					in_st[j] = 16;
				else
					j++;
			}

			if (in_st[j] == '&')
			{
				if (in_st[j + 1] != '&')
					in_st[j] = 12;
				else
					j++;
			}
		}
	}
	else
	{
		for (j = 0; in_st[j]; j++)
		{
			in_st[j] = (in_st[j] == 16 ? '|' : in_st[j]);
			in_st[j] = (in_st[j] == 12 ? '&' : in_st[j]);
		}
	}
	return (in_st);
}

/**
 * add_node - add separators and command lines in the lists
 *
 * @hd_s: head of separator list
 * @hd_l: head of command lines list
 * @in_st: input string
 * Return: no return
 */
void add_node(sep_lst **hd_s, ln_lst **hd_l, char *in_st)
{
	int j;
	char *lines;

	in_st = swap_chars(in_st, 0);

	for (j = 0; in_st[j]; j++)
	{
		if (in_st[j] == ';')
			add_end_sep(hd_s, in_st[j]);

		if (in_st[j] == '|' || in_st[j] == '&')
		{
			add_end_sep(hd_s, in_st[j]);
			j++;
		}
	}

	lines = str_tok(in_st, ";|&");
	do {
		lines = swap_chars(lines, 1);
		cmd_ln_end(hd_l, lines);
		lines = str_tok(NULL, ";|&");
	} while (lines != NULL);

}

/**
 * _next - go to the next command line stored
 *
 * @lst_s: separator list
 * @lst_l: command line list
 * @datashell: data structure
 * Return: no return
 */
void _next(sep_lst **lst_s, ln_lst **lst_l, dt_shell *datashell)
{
	int loop_sep;
	sep_lst *lt_s;
	ln_lst *lt_l;

	loop_sep = 1;
	lt_s = *lst_s;
	lt_l = *lst_l;

	while (lt_s != NULL && loop_sep)
	{
		if (datashell->lst_sts == 0)
		{
			if (lt_s->separator == '&' || lt_s->separator == ';')
				loop_sep = 0;
			if (lt_s->separator == '|')
				lt_l = lt_l->next, lt_s = lt_s->next;
		}
		else
		{
			if (lt_s->separator == '|' || lt_s->separator == ';')
				loop_sep = 0;
			if (lt_s->separator == '&')
				lt_l = lt_l->next, lt_s = lt_s->next;
		}
		if (lt_s != NULL && !loop_sep)
			lt_s = lt_s->next;
	}

	*lst_s = lt_s;
	*lst_l = lt_l;
}

/**
 * split_cmds - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datashell: data structure
 * @in: input string
 * Return: 0 to exit, 1 to continue
 */
int split_cmds(dt_shell *datashell, char *in)
{

	sep_lst *hd_s, *lst_s;
	ln_lst *hd_l, *lst_l;
	int loop;

	hd_s = NULL;
	hd_l = NULL;

	add_node(&hd_s, &hd_l, in);

	lst_s = hd_s;
	lst_l = hd_l;

	while (lst_l != NULL)
	{
		datashell->input = lst_l->cmd_ln;
		datashell->args = split_line(datashell->input);
		loop = exec_line(datashell);
		free(datashell->args);

		if (loop == 0)
			break;

		_next(&lst_s, &lst_l, datashell);

		if (lst_l != NULL)
			lst_l = lst_l->next;
	}

	free_sep_lst(&hd_s);
	free_ln_lst(&hd_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_line - tokenizes the input string
 *
 * @in: input string.
 * Return: string splitted.
 */
char **split_line(char *in)
{
	size_t bfsize;
	size_t i;
	char **tokens;
	char *token;

	bfsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bfsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = str_tok(in, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bfsize)
		{
			bfsize += TOK_BUFSIZE;
			tokens = reallocdp(tokens, i, sizeof(char *) * bfsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = str_tok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
