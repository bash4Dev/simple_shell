#include "shell.h"

/**
 * get_length - Get the lenght of a number.
 * @tint: type int number.
 * Return: Lenght of a number.
 */
int get_length(int tint)
{
	unsigned int n;
	int l = 1;

	if (tint < 0)
	{
		l++;
		n = tint * -1;
	}
	else
	{
		n = tint;
	}
	while (n > 9)
	{
		l++;
		n = n / 10;
	}

	return (l);
}
/**
 * _itoa - function converts int to string.
 * @i: type int number
 * Return: String.
 */
char *_itoa(int i)
{
	unsigned int n;
	int length = get_length(i);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (i < 0)
	{
		n = i * -1;
		buffer[0] = '-';
	}
	else
	{
		n = i;
	}

	length--;
	do {
		*(buffer + length) = (n % 10) + '0';
		n = n / 10;
		length--;
	}
	while (n > 0)
		;
	return (buffer);
}

/**
 * at_io - converts a string to an integer.
 * @st: input string.
 * Return: integer.
 */
int at_io(char *st)
{
	unsigned int c = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(st + c) != '\0')
	{
		if (size > 0 && (*(st + c) < '0' || *(st + c) > '9'))
			break;

		if (*(st + c) == '-')
			pn *= -1;

		if ((*(st + c) >= '0') && (*(st + c) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		c++;
	}

	for (i = c - size; i < c; i++)
	{
		oi = oi + ((*(st + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}
