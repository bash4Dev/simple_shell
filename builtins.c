#include "shell.h"

/**
 * exec_line - finds builtins and commands
 *
 * @datashell: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(dt_shell *datashell)
{
	int (*builtin)(dt_shell *datashell);

	if (datashell->args[0] == NULL)
		return (1);

	builtin = get_builtin(datashell->args[0]);

	if (builtin != NULL)
		return (builtin(datashell));

	return (exec_cmd(datashell));
}
