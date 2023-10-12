#include "shell.h"

/**
 * cd_sh - changes current directory
 *
 * @datashell: data relevant
 * Return: 1 on success
 */
int cd_sh(dt_shell *datashell)
{
        char *dir;
        int ishome, ishome2, isddash;

        dir = datashell->args[1];

        if (dir != NULL)
        {
                ishome = str_cmp("$HOME", dir);
                ishome2 = str_cmp("~", dir);
                isddash = str_cmp("--", dir);
        }

        if (dir == NULL || !ishome || !ishome2 || !isddash)
        {
                cd_home(datashell);
                return (1);
        }

        if (str_cmp("-", dir) == 0)
        {
                cd_prev(datashell);
                return (1);
        }

        if (str_cmp(".", dir) == 0 || str_cmp("..", dir) == 0)
        {
                cd_dot(datashell);
                return (1);
        }

        cd_to(datashell);

        return (1);
}

/**
 * cd_dot - changes to the parent directory
 *
 * @datashell: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(dt_shell *datashell)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = str_dup(pwd);
	set_env("OLDPWD", cp_pwd, datashell);
	dir = datashell->args[1];
	if (str_cmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, datashell);
		free(cp_pwd);
		return;
	}
	if (str_cmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	reverse_str(cp_strtok_pwd);
	cp_strtok_pwd = str_tok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = str_tok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			reverse_str(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, datashell);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datashell);
	}
	datashell->lst_sts = 0;
	free(cp_pwd);
}

/**
 * cd_to - changes to a directory given
 * by the user
 *
 * @datashell: data relevant (directories)
 * Return: no return
 */
void cd_to(dt_shell *datashell)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datashell->args[1];
	if (chdir(dir) == -1)
	{
		get_error(datashell, 2);
		return;
	}

	cp_pwd = str_dup(pwd);
	set_env("OLDPWD", cp_pwd, datashell);

	cp_dir = str_dup(dir);
	set_env("PWD", cp_dir, datashell);

	free(cp_pwd);
	free(cp_dir);

	datashell->lst_sts = 0;

	chdir(dir);
}

/**
 * cd_prev - changes to the previous directory
 *
 * @datashell: data relevant (environ)
 * Return: no return
 */
void cd_prev(dt_shell *datashell)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = str_dup(pwd);

	p_oldpwd = get_env("OLDPWD", datashell->environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = str_dup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, datashell);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datashell);
	else
		set_env("PWD", cp_oldpwd, datashell);

	p_pwd = get_env("PWD", datashell->environ);

	write(STDOUT_FILENO, p_pwd, str_len(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datashell->lst_sts = 0;

	chdir(p_pwd);
}

/**
 * cd_home - changes to home directory
 *
 * @datashell: data relevant (environ)
 * Return: no return
 */
void cd_home(dt_shell *datashell)
{
	char *p_pwd, *hm;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = str_dup(pwd);

	hm = get_env("HOME", datashell->environ);

	if (hm == NULL)
	{
		set_env("OLDPWD", p_pwd, datashell);
		free(p_pwd);
		return;
	}

	if (chdir(hm) == -1)
	{
		get_error(datashell, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datashell);
	set_env("PWD", hm, datashell);
	free(p_pwd);
	datashell->lst_sts = 0;
}
