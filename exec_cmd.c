#include "shell.h"

/**
 * is_cdir - checks ":" if is in the current directory.
 * @p: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_cdir(char *p, int *i)
{
	if (p[*i] == ':')
		return (1);

	while (p[*i] != ':' && p[*i])
	{
		*i += 1;
	}

	if (p[*i])
		*i += 1;

	return (0);
}

/**
 * _which - locates a command
 *
 * @command: command name
 * @environ: environment variable
 * Return: location of the command.
 */
char *_which(char *command, char **environ)
{
	char *p, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	p = get_env("PATH", environ);
	if (p)
	{
		ptr_path = str_dup(p);
		len_cmd = str_len(command);
		token_path = str_tok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdir(p, &i))
				if (stat(command, &st) == 0)
					return (command);
			len_dir = str_len(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			str_cpy(dir, token_path);
			str_cat(dir, "/");
			str_cat(dir, command);
			str_cat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = str_tok(NULL, ":");
		}
		free(ptr_path);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * is_executable - determines if is an executable
 *
 * @datashell: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int is_executable(dt_shell *datashell)
{
	struct stat st;
	int i;
	char *ipt;

	ipt = datashell->args[0];
	i = 0;

	while (ipt[i])
	{
		if (ipt[i] == '.')
		{
			if (ipt[i + 1] == '.')
				return (0);
			if (ipt[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (ipt[i] == '/' && i != 0)
		{
			if (ipt[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
		i++;
	}
	if (i == 0)
		return (0);

	if (stat(ipt + i, &st) == 0)
	{
		return (i);
	}
	get_error(datashell, 127);
	return (-1);
}

/**
 * check_err_cmd - verifies if user has permissions to access
 *
 * @dest_dir: destination directory
 * @datashell: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_err_cmd(char *dest_dir, dt_shell *datashell)
{
	if (dest_dir == NULL)
	{
		get_error(datashell, 127);
		return (1);
	}

	if (str_cmp(datashell->args[0], dest_dir) != 0)
	{
		if (access(dest_dir, X_OK) == -1)
		{
			get_error(datashell, 126);
			free(dest_dir);
			return (1);
		}
		free(dest_dir);
	}
	else
	{
		if (access(datashell->args[0], X_OK) == -1)
		{
			get_error(datashell, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exec_cmd - executes command lines
 *
 * @datashell: data relevant (args and input)
 * Return: 1 on success.
 */
int exec_cmd(dt_shell *datashell)
{
	pid_t pd;
	pid_t wpd;
	int s; /* State */
	int e; /* Execute */
	char *d; /* Directory */
	(void) wpd;

	e = is_executable(datashell);
	if (e == -1)
		return (1);
	if (e == 0)
	{
		d = _which(datashell->args[0], datashell->environ);
		if (check_err_cmd(d, datashell) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (e == 0)
			d = _which(datashell->args[0], datashell->environ);
		else
			d = datashell->args[0];
		execve(d + e, datashell->args, datashell->environ);
	}
	else if (pd < 0)
	{
		perror(datashell->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &s, WUNTRACED);
		} while (!WIFEXITED(s) && !WIFSIGNALED(s));
	}

	datashell->lst_sts = s / 256;
	return (1);
}
