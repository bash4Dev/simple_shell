#include "shell.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @datashell: data structure (args and input)
 * Return: Return 0
*/
int get_help(dt_shell *datashell)
{

	if (datashell->args[1] == 0)
		help_gen();
	else if (str_cmp(datashell->args[1], "setenv") == 0)
		help_setenv();
	else if (str_cmp(datashell->args[1], "env") == 0)
		help_env();
	else if (str_cmp(datashell->args[1], "unsetenv") == 0)
		help_unsetenv();
	else if (str_cmp(datashell->args[1], "help") == 0)
		_help();
	else if (str_cmp(datashell->args[1], "exit") == 0)
		help_exit();
	else if (str_cmp(datashell->args[1], "cd") == 0)
		help_cd();
	else if (str_cmp(datashell->args[1], "alias") == 0)
		help_alias();
	else
		write(STDERR_FILENO, datashell->args[0],
		      str_len(datashell->args[0]));

	datashell->lst_sts = 0;
	return (1);
}
