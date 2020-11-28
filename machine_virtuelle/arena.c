/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 20:24:48 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/10 12:04:35 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"


t_visu  *get_visu(t_visu *visu)
{
	static t_visu	*v;

	if (visu)
		v = visu;
	return (v);
}

static	void			print_byt(const void *addr)
{
	const char			*str = "0123456789ABCDEF";
	uint8_t				*p;

	p = (uint8_t *)addr;
	ft_putchar(str[(p[0] / 16) % 16]);
	ft_putchar(str[p[0] % 16]);
	ft_putstr(" ");
}

static	void			print_index_hex(const void *addr)
{
	const char			*str = "0123456789ABCDEF";
	uint8_t				*p;

	p = (uint8_t *)addr;
	ft_putchar(str[(p[0] / 16) % 16]);
	ft_putchar(str[p[0] % 16]);
}

t_corewar				*get_corewar(t_corewar *lst)
{
	static t_corewar	*p;

	if (lst)
		p = lst;
	return (p);
}

uint8_t					*ft_get_arena(void)
{
	uint8_t				*str;

	if (!(str = (uint8_t *)malloc(sizeof(uint8_t) * 4096)))
		return (NULL);
	ft_memset((void *)str, 0, sizeof(uint8_t) * 4096);
	return (str);
}
void print_winer(void)
{
	t_corewar			*war;
	int					i;
	int					id;
	int					last_live;

	war = get_corewar(0);
	i = -1;
	id = 0;
	last_live = 0;
	while (++i < war->nbr_fighters)
	{
		if (war->players[i].last_cycle_to_live > last_live)
		{
			id = i;
			last_live = war->players[i].last_cycle_to_live;
		}
	}
	ft_printf("Contestant 1, \" %s \", has won !\n",\
	war->players[id].data_file->prog_name);
}

void					ft_print_arena(void)
{
	t_corewar			*war;
	int					i;
	char			count;

	war = get_corewar(0);
	i = -1;
	while (++i < 4096)
	{
		
		if (i != 0 && !(i % 64))
			ft_putchar('\n');
		if (i == 0 || !((i) % 64))
		{
			ft_putstr("0x");
			count = ((i >> 8) & 0xff);
			print_index_hex(&count);
			count = (i & 0xff);
			print_index_hex(&count);		
			ft_putstr(" : ");
		}
			
		print_byt(&war->arena[i]);
	}
	ft_putchar('\n');
	ft_putchar('\n');
}

void					print_game(void)
{
	t_corewar			*war;
	int					i;

	war = get_corewar(0);
	i = -1;
	ft_putendl("Introducting contestants ...");
	while (++i < war->nbr_fighters)
	{
		ft_printf("* Player %d, weighing 615\
		bytes, \"%s\" (\"%s\") !\n", i + 1,
		war->players[i].data_file->prog_name,\
		war->players[i].data_file->comment);
	}
}
