#include "shell.h"

/**
 * bring_line - assigns the line var for get_line
 * @lineptr: Buffer that store the input str
 * @buffer: str that is been called to line
 * @l: size of line
 * @b: size of buffer
 */
void bring_line(char **line_ptr, size_t *l, char *buffer, size_t b)
{

	if (*line_ptr == NULL)
	{
		if  (b > BUFSIZE)
			*l = b;

		else
			*l = BUFSIZE;
		*line_ptr = buffer;
	}
	else if (*l < b)
	{
		if (b > BUFSIZE)
			*l = b;
		else
			*l = BUFSIZE;
		*line_ptr = buffer;
	}
	else
	{
		str_cpy(*line_ptr, buffer);
		free(buffer);
	}
}
/**
 * get_line - Read inpt from stream
 * @line_ptr: buffer that stores the input
 * @sl: size of lineptr
 * @stream: stream to read from
 * Return: The number of bytes
 */
ssize_t get_line(char **line_ptr, size_t *sl, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t retval;
	char *buffer;
	char t = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = re_alloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	bring_line(line_ptr, sl, buffer, input);
	retval = input;
	if (i != 0)
		input = 0;
	return (retval);
}

/**
 * rd_line - reads the input strings
 *
 * @gline: return value of getline function
 * Return: input string
 */
char *rd_line(int *gline)
{
	char *in = NULL;
	size_t bfsize = 0;

	*gline = getline(&in, &bfsize, stdin);
	return (in);
}
