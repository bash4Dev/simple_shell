#include "shell.h"

 * @str: input string.
 * @dlm: delimiter.
 *
 * Return: string splited.
 */
char *str_tok(char str[], const char *dlm)
{
        static char *spl, *str_e;
        char *str_s;
        unsigned int k, bool;

        if (str != NULL)
        {
                if (cmp_chars(str, dlm))
                        return (NULL);
                spl = str; /*Store first address*/
                k = str_len(str);
                str_e = &str[k]; /*Store last address*/
        }
        str_s = spl;
        if (str_s == str_e) /*Reaching the end*/
                return (NULL);

        for (bool = 0; *spl; spl++)
        {
                /*Breaking loop finding the next token*/
                if (spl != str_s)
                        if (*spl && *(spl - 1) == '\0')
                                break;
                /*Replacing delimiter for null char*/
                for (k = 0; dlm[k]; k++)
                {
                        if (*spl == dlm[k])
                        {
                                *spl = '\0';
                                if (spl == str_s)
                                        str_s++;
                                break;
                        }
                }
                if (bool == 0 && *spl) /*Str != Delim*/
                        bool = 1;
        }
        if (bool == 0) /*Str == Delim*/
                return (NULL);
        return (str_s);
}

/**
 * str_cat - concatenate two strings
 * @dst: char pointer to the dest of the copied str
 * @s: const char pointer to the src of str
 * Return: destination
 */
char *str_cat(char *dst, const char *s)
{
	int a;
	int b;

	for (a = 0; dst[a] != '\0'; a++)
		;

	for (b = 0; s[b] != '\0'; b++)
	{
		dst[a] = s[b];
		a++;
	}

	dst[a] = '\0';
	return (dst);
}

/**
 * *str_cpy - Copies the string pointed to by src.
 * @dst: Type char pointer the dest of the copied str
 * @s: Type char pointer the source of str
 * Return: the dest.
 */
char *str_cpy(char *dst, char *s)
{

	size_t e;

	for (e = 0; s[e] != '\0'; e++)
	{
		dst[e] = s[e];
	}
	dst[e] = '\0';

	return (dst);
}

/**
 * str_cmp - Function that compares two strings.
 * @str_a: type str compared
 * @str_b: type str compared
 * Return: Always 0.
 */
int str_cmp(char *str_a, char *str_b)
{
	int k;
	
	k = 0;
	while (str_a[k] == str_b[k] && str_a[k] != '\0')
	{
	k++;
	}
	if (str_a[k] > str_b[k])
	{
		return 1;
	}
	else if (str_a[k] < str_b[k])
	{
		return -1;
	}
	else
	{
		return 0;
	}

/*	k = 0;
	while(str_a[k] == str_b[k] && str_a[k])
	{
		if(str_a[k] > str_b[k])
			return (1);
		if (str_a[k] < str_b[k])
			return (-1);
		k++;
		return (0);
	} */
}

/**
 * str_spn - gets the length of a prefix substring.
 * @seg: initial segment.
 * @acpt: accepted bytes.
 * Return: the number of accepted bytes.
 */
int str_spn(char *seg, char *acpt)
{
	int k, l, bool;

	for (k = 0; *(seg + k) != '\0'; k++)
	{
		bool = 1;
		for (l = 0; *(acpt + l) != '\0'; l++)
		{
			if (*(seg + k) == *(acpt + l))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (k);
}
