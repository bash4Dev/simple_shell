#include "shell.h"

/**
 * del_comments - deletes comments from the input
 *
 * @in_st: input string
 * Return: input without comments
 */
char *del_comments(char *in_st)
{
	int j, upto;

	upto = 0;
	for (j = 0; in_st[j]; j++)
	{
		if (in_st[j] == '#')
		{
			if (j == 0)
			{
				free(in_st);
				return (NULL);
			}

			if (in_st[j - 1] == ' ' || in_st[j - 1] == '\t' || in_st[j - 1] == ';')
				upto = j;
		}
	}

	if (upto != 0)
	{
		in_st = re_alloc(in_st, j, upto + 1);
		in_st[upto] = '\0';
	}

	return (in_st);
}

/**
 * sh_loop - Loop of shell
 * @datashell: data relevant (av, input, args)
 *
 * Return: no return.
 */
void sh_loop(dt_shell *datashell)
{
	int lp, gline;
	char *in;

	lp = 1;
	while (lp == 1)
	{
		write(STDIN_FILENO, "~$ ", 4);
		in = rd_line(&gline);
		if (gline != -1)
		{
			in = del_comments(in);
			if (in == NULL)
				continue;

			if (check_syntax_err(datashell, in) == 1)
			{
				datashell->lst_sts = 2;
				free(in);
				continue;
			}
			in = replace_var(in, datashell);
			lp = split_cmds(datashell, in);
			datashell->line_ct += 1;
			free(in);
		}
		else
		{
			lp = 0;
			free(in);
		}
	}
}
