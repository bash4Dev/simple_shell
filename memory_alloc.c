#include "shell.h"

/**
 * mem_cp - copies infor between void pointers.
 * @nw_ptr: destination pointer.
 * @scr_ptr: source pointer.
 * @sz: size of the new pointer.
 *
 * Return: no return.
 */
void mem_cp(void *nw_ptr, const void *scr_ptr, unsigned int sz)
{
	char *ch_ptr = (char *)scr_ptr;
	char *ch_nptr = (char *)nw_ptr;
	unsigned int k;

	k = 0;
	while (k < sz)
	{
		ch_nptr[k] = ch_ptr[k];
		k++;
	}
}

/**
 * re_alloc - reallocates a memory block.
 * @pt: pointer to the memory previously allocated.
 * @osize: size, in bytes, of the allocated space of ptr.
 * @nsize: new size, in bytes, of the new memory block.
 *
 * Return: pointer.
 * if nsize == osize, returns pt without changes.
 * if malloc fails, returns NULL.
 */
void *re_alloc(void *pt, unsigned int osize, unsigned int nsize)
{
	void *new_pt;

	if (pt == NULL)
		return (malloc(nsize));

	if (nsize == 0)
	{
		free(pt);
		return (NULL);
	}

	if (nsize == osize)
		return (pt);

	new_pt = malloc(nsize);
	if (new_pt == NULL)
		return (NULL);

	if (nsize < osize)
		mem_cp(new_pt, pt, nsize);
	else
		mem_cp(new_pt, pt, osize);

	free(pt);
	return (new_pt);
}

/**
 * reallocdp - reallocates a memory block of a double pointer.
 * @prev_mem: double pointer to the memory previously allocated.
 * @osize: size, in bytes, of the allocated space of ptr.
 * @nsize: new size, in bytes, of the new memory block.
 *
 * Return: pt.
 * if nsize == osize, returns pt without changes.
 * if malloc fails, returns NULL.
 */
char **reallocdp(char **prev_mem, unsigned int osize, unsigned int nsize)
{
	char **new_pt;
	unsigned int k;

	if (prev_mem == NULL)
		return (malloc(sizeof(char *) * nsize));

	if (nsize == osize)
		return (prev_mem);

	new_pt = malloc(sizeof(char *) * nsize);
	if (new_pt == NULL)
		return (NULL);

	for (k = 0; k < osize; k++)
		new_pt[k] = prev_mem[k];

	free(prev_mem);
	return (new_pt);
}
