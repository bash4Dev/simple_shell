#include "shell.h"

/**
 * get_builtin - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*get_builtin(char *cmd))(dt_shell *)
{
	int i;

	builtin_t builtin[] = {
		{ "env", _env },
		{ "exit", exit_sh },
		{ "setenv", _set_env },
		{ "unsetenv", unset_env },
		{ "cd", cd_sh },
		{ "help", get_help },
		{ NULL, NULL }
	};

	for (i = 0; builtin[i].nm; i++)
	{
		if (str_cmp(builtin[i].nm, cmd) == 0)
			break;
	}

	return (builtin[i].ptr_f);
}
