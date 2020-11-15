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
t_header *ft_free_head(t_header **new)
{
	ft_memdel((void **)new);
	return (NULL);
}

t_header *ft_cin_file(char *file)
{
	t_header *new;
	int fd;
	int s;

	if (!(new = (t_header *)malloc(sizeof(t_header))))
		return (NULL);
	ft_memset((void *)new, 0, sizeof(t_header));
	if ((fd = open(file, O_RDONLY)) < 0)
		return (ft_free_head(&new));
	if ((s = read(fd, (void *)&new->magic, 4)) < 0 || s != 4)
		return (ft_free_head(&new));
	if ((s = read(fd, (void *)new->prog_name, (PROG_NAME_LENGTH + 4))) < 0 ||
	 s > (PROG_NAME_LENGTH + 4))
		return (ft_free_head(&new));
	if ((s = read(fd, (void *)&new->prog_size, 4)) < 0 || s != 4)
		return (ft_free_head(&new));
	if ((s = read(fd, (void *)new->comment, (COMMENT_LENGTH + 4))) < 0 ||
	 s > (COMMENT_LENGTH + 4))
		return (ft_free_head(&new));
	if ((s = read(fd, (void *)new->champ, CHAMP_MAX_SIZE)) < 0 || s > CHAMP_MAX_SIZE)
		return (ft_free_head(&new));
	return (new);
}
