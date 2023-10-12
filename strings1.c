#include "shell.h"

/**
 * cmp_chars - compare chars of strings
 * @str: input string.
 * @dlm: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_chars(char str[], const char *dlm)
{
	unsigned int k, l, j;

	for (k = 0, j = 0; str[k]; k++)
	{
		for (l = 0; dlm[l]; l++)
		{
			if (str[k] == dlm[l])
			{
				j++;
				break;
			}
		}
	}
	if (k == j)
		return (1);
	return (0);
}

/**
 * is_digit - defines if string passed is a number
 *
 * @in_st: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int is_digit(const char *in_st)
{
	unsigned int k;

	for (k = 0; in_st[k]; k++)
	{
		if (in_st[k] < 48 || in_st[k] > 57)
			return (0);
	}
	return (1);
}

/**
 * reverse_str - reverses a string.
 * @in_st: input string.
 * Return: no return.
 */
void reverse_str(char *in_st)
{
        int ct = 0, k, l;
        char *s, tmp;

        while (ct >= 0)
        {
                if (in_st[ct] == '\0')
                        break;
                ct++;
        }
        s = in_st;

        for (k = 0; k < (ct - 1); k++)
        {
                for (l = k + 1; l > 0; l--)
                {
                        tmp = *(s + l);
                        *(s + l) = *(s + (l - 1));
                        *(s + (l - 1)) = tmp;
                }
        }
}
