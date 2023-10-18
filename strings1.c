#include "shell.h"

/**
 * str_dup - duplicates a str in the heap memory.
 * @st: Type char pointer str
 * Return: duplicated str
 */
char *str_dup(const char *st)
{
	char *nw;
	size_t length;

	length = str_len(st);
	nw = malloc(sizeof(char) * (length + 1));
	if (nw == NULL)
		return (NULL);
	mem_cp(nw, st, length + 1);
	return (nw);
}

/**
 * str_len - Returns the lenght of a string.
 * @str: Type char pointer
 * Return: Always 0.
 */
int str_len(const char *str)
{
	int l;

	for (l = 0; str[l] != 0; l++)
	{
	}
	return (l);
}

/**
 * str_chr - locates a character in a string,
 * @st: string.
 * @ch: character.
 * Return: the pointer to the first occurrence of the character c.
 */
char *str_chr(char *st, char ch)
{
	unsigned int k = 0;

	for (; *(st + k) != '\0'; k++)
		if (*(st + k) == ch)
			return (st + k);
	if (*(st + k) == ch)
		return (st + k);
	return ('\0');
}
