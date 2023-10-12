#include "shell.h"

/**
 * exit_sh - exits the shell
 *
 * @datashell: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_sh(dt_shell *datashell)
{
	unsigned int ust;
	int _isdigit;
	int _strlen;
	int big_numb;

	if (datashell->args[1] != NULL)
	{
		ust = at_io(datashell->args[1]);
		_isdigit = is_digit(datashell->args[1]);
		_strlen = str_len(datashell->args[1]);
		big_numb = ust > (unsigned int)INT_MAX;
		if (!_isdigit || _strlen > 10 || big_numb)
		{
			get_error(datashell, 2);
			datashell->lst_sts = 2;
			return (1);
		}
		datashell->lst_sts = (ust % 256);
	}
	return (0);
}
