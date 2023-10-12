#include "shell.h"

/**
 * check_env - checks if the typed variable is an env variable
 *
 * @hd: head of linked list
 * @input: input string
 * @data: data structure
 * Return: no return
 */
void check_env(var_list **hd, char *input, dt_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = str_len(_envr[row] + chr + 1);
				add_rvar_node(hd, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (input[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; input[j]; j++)
	{
		if (input[j] == ' ' || input[j] == '\t' || input[j] == ';' || input[j] == '\n')
			break;
	}

	add_rvar_node(hd, j, NULL, 0);
}

/**
 * check_vars - check if the typed variable is $$ or $?
 *
 * @hd: head of the linked list
 * @in_st: input string
 * @lst: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_var(var_list **hd, char *in_st, char *lst, dt_shell *data)
{
	int i, last_st, lpd;

	last_st = str_len(lst);
	lpd = str_len(data->sh_pid);

	for (i = 0; in_st[i]; i++)
	{
		if (in_st[i] == '$')
		{
			if (in_st[i + 1] == '?')
				add_rvar_node(hd, 2, lst, last_st), i++;
			else if (in_st[i + 1] == '$')
				add_rvar_node(hd, 2, data->sh_pid, lpd), i++;
			else if (in_st[i + 1] == '\n')
				add_rvar_node(hd, 0, NULL, 0);
			else if (in_st[i + 1] == '\0')
				add_rvar_node(hd, 0, NULL, 0);
			else if (in_st[i + 1] == ' ')
				add_rvar_node(hd, 0, NULL, 0);
			else if (in_st[i + 1] == '\t')
				add_rvar_node(hd, 0, NULL, 0);
			else if (in_st[i + 1] == ';')
				add_rvar_node(hd, 0, NULL, 0);
			else
				check_env(hd, in_st + i, data);
		}
	}

	return (i);
}

/**
 * rep_input - replaces string into variables
 *
 * @hd: head of the linked list
 * @input: input string
 * @n_input: new input string (replaced)
 * @nlength: new length
 * Return: replaced string
 */
char *rep_input(var_list **hd, char *input, char *n_input, int nlength)
{
	var_list *idx;
	int i, j, k;

	idx = *hd;
	for (j = i = 0; i < nlength; i++)
	{
		if (input[j] == '$')
		{
			if (!(idx->var_lngth) && !(idx->_val))
			{
				n_input[i] = input[j];
				j++;
			}
			else if (idx->var_lngth && !(idx->_val))
			{
				for (k = 0; k < idx->var_lngth; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < idx->_val; k++)
				{
					n_input[i] = idx->var_vl[k];
					i++;
				}
				j += (idx->var_lngth);
				i--;
			}
			idx = idx->next;
		}
		else
		{
			n_input[i] = input[j];
			j++;
		}
	}

	return (n_input);
}

/**
 * replace_var - calls functions to replace string into vars
 *
 * @input: input string
 * @datashell: data structure
 * Return: replaced string
 */
char *replace_var(char *input, dt_shell *datashell)
{
	var_list *hd, *idx;
	char *st, *nw_input;
	int olength, nlength;

	st = _itoa(datashell->lst_sts);
	hd = NULL;

	olength = check_var(&hd, input, st, datashell);

	if (hd == NULL)
	{
		free(st);
		return (input);
	}

	idx = hd;
	nlength = 0;

	while (idx != NULL)
	{
		nlength += (idx->_val - idx->var_lngth);
		idx = idx->next;
	}

	nlength += olength;

	nw_input = malloc(sizeof(char) * (nlength + 1));
	nw_input[nlength] = '\0';

	nw_input = rep_input(&hd, input, nw_input, nlength);

	free(input);
	free(st);
	free_rvar_list(&hd);

	return (nw_input);
}
