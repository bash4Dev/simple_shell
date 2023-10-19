#include "shell.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @hd: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
var_list *add_rvar_node(var_list **hd, int lvar, char *val, int lval)
{
	var_list *nw, *tmp;

	nw = malloc(sizeof(var_list));
	if (nw == NULL)
		return (NULL);

	nw->var_lngth = lvar;
	nw->var_vl = val;
	nw->_val = lval;

	nw->next = NULL;
	tmp = *hd;

	if (tmp == NULL)
	{
		*hd = nw;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = nw;
	}
	return (*hd);
}

/**
 * add_end_sep - adds a separator found at the end
 * of a sep_list.
 * @hd: head of the linked list.
 * @s: separator found (; | &).
 * Return: address of the head.
 */
sep_lst *add_end_sep(sep_lst **hd, char s)
{
	sep_lst *nw, *tmp;

	nw = malloc(sizeof(sep_lst));
	if (nw == NULL)
		return (NULL);

	nw->separator = s;
	nw->next = NULL;
	tmp = *hd;

	if (tmp == NULL)
	{
		*hd = nw;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = nw;
	}

	return (*hd);
}

/**
 * cmd_ln_end - adds a command line at the end
 * of a line_list.
 * @hd: head of the linked list.
 * @cmd_ln: command line.
 * Return: address of the head.
 */
ln_lst *cmd_ln_end(ln_lst **hd, char *cmd_ln)
{
	ln_lst *nw, *tmp;

	nw = malloc(sizeof(ln_lst));
	if (nw == NULL)
		return (NULL);

	nw->cmd_ln = cmd_ln;
	nw->next = NULL;
	tmp = *hd;

	if (tmp == NULL)
	{
		*hd = nw;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = nw;
	}

	return (*hd);
}

/**
 * free_ln_lst - frees a line_list
 * @hd: head of the linked list.
 * Return: no return.
 */
void free_ln_lst(ln_lst **hd)
{
	ln_lst *tmp;
	ln_lst *cr;

	if (hd != NULL)
	{
		cr = *hd;
		while ((tmp = cr) != NULL)
		{
			cr = cr->next;
			free(tmp);
		}
		*hd = NULL;
	}
}

/**
 * free_rvar_list - frees a r_var list
 * @hd: head of the linked list.
 * Return: no return.
 */
void free_rvar_list(var_list **hd)
{
	var_list *tmp;
	var_list *cr;

	if (hd != NULL)
	{
		cr = *hd;
		while ((tmp = cr) != NULL)
		{
			cr = cr->next;
			free(tmp);
		}
		*hd = NULL;
	}
}
