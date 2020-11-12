/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/12 12:38:07 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** in this file main programe principall
**
**
**
**
**
**
**
**
*/

#include "../include/corewar.h"

static void manage(t_corewar *war, int argc, char **argv)
{
	t_header *lst;
	int i;
	int position;

	position = 0;

	if (argc == 1)
		return;

	i = 0;
	war->nbr_fighters = argc - 1;
	ft_init_process(war);
	war->arena = ft_get_arena();
	while (++i < argc)
	{

		lst = ft_cin_file(argv[i]);

		ft_memcpy(&war->arena[position], lst->champ, hex(addr_to_hex(&lst->prog_size, 4)));
		position += 682;
	}
}

void Free_Process(t_process *p)
{
	if (p->next)
		Free_Process(p->next);
	ft_memdel((void **)&p);
}

void Free_Corewar(t_corewar *war)
{
	int i;

	i = -1;
	ft_memdel((void **)&war->arena);
	while (++i < war->nbr_fighters)
	{
		ft_memdel((void **)&war->players[i].data_file);
		Free_Process(war->players[i].process);
	}
	ft_memdel((void **)&war);
}

int main(int argc, char **argv)
{
	t_corewar	*war;
	t_visu		*visu;

	if (!(visu = (t_visu *)ft_memalloc(sizeof(t_visu))))
		return (1);
	border_maker(visu);
	if (!(war = (t_corewar *)malloc(sizeof(t_corewar))))
		return (1);
	ft_memset((void *)war, 0, sizeof(t_corewar));
	manage(war, argc, argv);
	get_struct(war);
	ft_loop(visu);
	// Free_Corewar(war);

	return (0);
}