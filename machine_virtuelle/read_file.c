/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 18:26:19 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

/*
** func test func read_fille 
*/

void print(const void *addr, size_t size)
{
	const char *str = "0123456789abcdef";
	size_t i;
	size_t j;
	char_t *p;

	p = (char_t *)addr;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < 16 && i + j < size)
		{
			ft_putchar(str[(p[i + j] / 16) % 16]);
			ft_putchar(str[p[i + j] % 16]);
			if (j % 2)
				ft_putchar(' ');
			j++;
		}
		ft_putchar('\n');
		i += 16;
	}
}

void ft_cout(t_header *data)
{
	ft_putendl("111");
	print(&data->magic, 4);
	printf("\n|%u|\n", data->magic);
	print(data->prog_name, PROG_NAME_LENGTH + 4);
	print(&data->prog_size, 4);
	print(data->comment, COMMENT_LENGTH + 4);
	print(data->champ, 993);
	ft_putendl("222111");
}

/*
** in this file read data for file.cor 
** and verfie data for fille
**
**
**
**
**
**
**
*/

t_header *ft_cin_file(char *file)
{
	int fd;
	t_header *new;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (!(new = (t_header *)malloc(sizeof(t_header))))
		return (NULL);
	ft_memset((void *)new, 0, sizeof(t_header));
	if ((read(fd, (void *)&new->magic, sizeof(unsigned int))) < 0)
		return (NULL);
	if ((read(fd, (void *)new->prog_name, sizeof(char) * (PROG_NAME_LENGTH + 4))) < 0)
		return (NULL);
	if ((read(fd, (void *)&new->prog_size, sizeof(unsigned int))) < 0)
		return (NULL);
	if ((read(fd, (void *)new->comment, sizeof(char) * (COMMENT_LENGTH + 4))) < 0)
		return (NULL);
	if ((read(fd, (void *)new->champ, sizeof(char_t) * (CHAMP_MAX_SIZE))) < 0)
		return (NULL);
	return (new);
}
