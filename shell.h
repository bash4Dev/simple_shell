#ifndef  _SHELL_H_ 
#define  _SHELL_H_

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \a\n\t\r"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct dt_sh - struct that contains all relevant data on runtime
 * @av: argument vector.
 * @input: command line written by the user.
 * @args: tokens of the command line.
 * @lst_sts: last status of the shell
 * @line_ct: lines counter
 * @environ: environment variable.
 * @sh_pid: process ID of the shell
 */
typedef struct dt_sh
{
	char **av;
	char *input;
	char **args;
	int lst_sts;
	int line_ct;
	char **environ;
	char *sh_pid;
} dt_shell;

/**
 * struct sep_lst_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_lst_s
{
	char separator;
	struct sep_lst_s *next;
} sep_lst;

/**
 * struct ln_lst_s - single linked list
 * @cmd_ln: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct ln_lst_s
{
	char *cmd_ln;
	struct ln_lst_s *next;
} ln_lst;

/**
 * struct s_lnkd_list - single linked list
 * @var_lngth: length of the variable
 * @var_vl: value of the variable
 * @_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct s_lnkd_list
{
	int var_lngth;
	char *var_vl;
	int _val;
	struct s_lnkd_list *next;
} var_list;

/**
 * struct builtin_s - Builtin struct for command args.
 * @nm: The name of the command builtin i.e cd, exit, env
 * @ptr_f: data type pointer function.
 */
typedef struct builtin_s
{
	char *nm;
	int (*ptr_f)(dt_shell *datashell);
} builtin_t;

/*  */
sep_lst *add_end_sep(sep_lst **hd, char s);
void free_sep_lst(sep_lst **hd);
ln_lst *cmd_ln_end(ln_lst **hd, char *cmd_ln);
void free_ln_lst(ln_lst **hd);

/*  */
var_list *add_rvar_node(var_list **head, int lvar, char *var, int lval);
void free_rvar_list(var_list **head);

/* string functions 0 */
char *str_cat(char *dst, const char *s);
char *str_cpy(char *dst, char *s);
int str_cmp(char *str_a, char *str_b);
char *str_chr(char *st, char ch);
int str_spn(char *seg, char *acpt);

/* memory allocations */
void mem_cp(void *nw_ptr, const void *scr_ptr, unsigned int sz);
void *re_alloc(void *pt, unsigned int osize, unsigned int nsize);
char **reallocdp(char **prev_mem, unsigned int osize, unsigned int nsize);

/* String functions 1 */
char *str_dup(const char *st);
int str_len(const char *str);
int cmp_chars(char str[], const char *dlm);
char *str_tok(char str[], const char *dlm);
int is_digit(const char *in_st);

/* function that reverses a str */
void reverse_str(char *in_st);

/* Syntax error msg */
int rep_char(char *in, int idx);
int err_sep_op(char *in, int idx, char lst);
int first_char(char *in, int *idx);
void print_syntax_err(dt_shell *datashell, char *in, int idx, int bool);
int check_syntax_err(dt_shell *datashell, char *in);

/* shell looping functions */
char *del_comments(char *in_st);
void sh_loop(dt_shell *datashell);

/* read lines function */
char *rd_line(int *gline);

/*  */
char *swap_chars(char *in_st, int bool);
void add_node(sep_lst **hd_s, ln_lst **hd_l, char *in_st);
void _next(sep_lst **lst_s, ln_lst **lst_l, dt_shell *datashell);
int split_cmds(dt_shell *datashell, char *in);
char **split_line(char *in);

/*  */
void check_env(var_list **hd, char *input, dt_shell *data);
int check_var(var_list **hd, char *in_st, char *lst, dt_shell *data);
char *rep_input(var_list **hd, char *input, char *n_input, int nlength);
char *replace_var(char *input, dt_shell *datashell);

/*  */
void bring_line(char **line_ptr, size_t *l, char *buffer, size_t b);
ssize_t get_line(char **line_ptr, size_t *sl, FILE *stream);

/*  */
int exec_line(dt_shell *datashell);

/*  */
int is_cdir(char *p, int *i);
char *_which(char *command, char **_environ);
int is_executable(dt_shell *datashell);
int check_err_cmd(char *dest_dir, dt_shell *datashell);
int exec_cmd(dt_shell *datashell);

/*  */
char *get_env(const char *name, char **environ);
int _env(dt_shell *datashell);

/*  */
char *cp_info(char *nm, char *value);
void set_env(char *name, char *value, dt_shell *datashell);
int _set_env(dt_shell *datashell);
int unset_env(dt_shell *datashell);

/* Change dir */
void cd_dot(dt_shell *datashell);
void cd_to(dt_shell *datashell);
void cd_prev(dt_shell *datashell);
void cd_home(dt_shell *datashell);

/* cd_shell */
int cd_sh(dt_shell *datashell);

/* get_builtin */
int (*get_builtin(char *cmd))(dt_shell *datashell);

/* _exit_shell */
int exit_sh(dt_shell *datashell);

/* stdlib */
int get_length(int tint);
char *_itoa(int i);
int at_io(char *st);

/*  */
char *str_cat_cd(dt_shell *, char *, char *, char *);
char *err_get_cd(dt_shell *datashell);
char *err_not_found(dt_shell *datashell);
char *err_exit_sh(dt_shell *datashell);

char *error_alias(char **args);
char *env_error(dt_shell *datashell);
char *syntax_err(char **args);
char *err_permission(char **args);
char *path_err126(dt_shell *datashell);


/*  */
int get_error(dt_shell *datashell, int eval);

/*  */
void get_sigint(int s);

/*  */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_gen(void);
void help_exit(void);

/*  */
void _help(void);
void help_alias(void);
void help_cd(void);

int get_help(dt_shell *datashell);

#endif
