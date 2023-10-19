#include "shell.h"

/**
 * cmp_env - compares env variables names
 * with the name passed.
 * @nenv: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if are not equal. Another value if they are.
 */
int cmp_env(const char *nenv, const char *name)
{
	int i;
	
	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * get_env - get an environment variable
 * @name: name of the environment variable
 * @environ: environment variable
 *
 * Return: value of the environment variable if is found.
 * In other case, returns NULL.
 */
char *get_env(const char *name, char **environ)
{
	char *ptr_env;
	int i, move;

        /* Initialize ptr_env value */
	ptr_env = NULL;
	move = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; environ[i]; i++)
	{
		/* If name and env are equal */
		move = cmp_env(environ[i], name);
		if (move)
		{
			ptr_env = environ;
			break;
		}
	}
	return (ptr_env + move);
}

/**
 * cp_info - copies info to create
 * a new env or alias
 * @nm: name (env or alias)
 * @value: value (env or alias)
 *
 * Return: new env or alias.
 */
char *cp_info(char *nm, char *value)
{
	char *new;
	int len_nm, len_val, len;

	len_nm = str_len(nm);
	len_val = str_len(value);
	len = len_nm + len_val + 2;
	new = malloc(sizeof(char) * (len));
	str_cpy(new, nm);
	str_cat(new, "=");
	str_cat(new, value);
	str_cat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @datashell: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, dt_shell *datashell)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; datashell->environ[i]; i++)
	{
		var_env = str_dup(datashell->environ[i]);
		name_env = str_tok(var_env, "=");
		if (str_cmp(name_env, name) == 0)
		{
			free(datashell->environ[i]);
			datashell->environ[i] = cp_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	datashell->environ = reallocdp(datashell->environ, i, sizeof(char *) * (i + 2));
	datashell->environ[i] = cp_info(name, value);
	datashell->environ[i + 1] = NULL;
}

/**
 * _set_env - compares env variables names
 * with the name passed.
 * @datashell: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _set_env(dt_shell *datashell)
{

	if (datashell->args[1] == NULL || datashell->args[2] == NULL)
	{
		get_error(datashell, -1);
		return (1);
	}

	set_env(datashell->args[1], datashell->args[2], datashell);

	return (1);
}

/**
 * unset_env - deletes a environment variable
 *
 * @datashell: data relevant (env name)
 *
 * Return: 1 on success.
 */
int unset_env(dt_shell *datashell)
{
	char **realloc_env;
	char *var_env, *name_env;
	int i, j, k;

	if (datashell->args[1] == NULL)
	{
		get_error(datashell, -1);
		return (1);
	}
	k = -1;
	for (i = 0; datashell->environ[i]; i++)
	{
		var_env = str_dup(datashell->environ[i]);
		name_env = str_tok(var_env, "=");
		if (str_cmp(name_env, datashell->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(datashell, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; datashell->environ[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = datashell->environ[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(datashell->environ[k]);
	free(datashell->environ);
	datashell->environ = realloc_env;
	return (1);
}
