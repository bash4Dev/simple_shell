#include "shell.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @datashell: data structure that contains arguments
 * @err_val: error value
 * Return: error
 */
int get_error(dt_shell *datashell, int err_val)
{
	char *err;

	if (err_val == -1)
	{
		err = env_error(datashell);
	}
	else if (err_val == 126)
	{
		err = path_err126(datashell);
	}
	else if (err_val == 127)
	{
		err = err_not_found(datashell);
	} else if (err_val == 2)
	{
		if (str_cmp("exit", datashell->args[0]) == 0)
		{
			err = err_exit_sh(datashell);
		}
		else if (str_cmp("cd", datashell->args[0]) == 0)
		{
			err = err_get_cd(datashell);
		}
	}

	if (err)
	{
		write(STDERR_FILENO, err, str_len(err));
		free(err);
	}

	datashell->lst_sts = err_val;
	return (err_val);
}
