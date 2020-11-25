/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/25 10:24:30 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void			free_process(t_process *p)
{
	if (p->next)
		free_process(p->next);
	ft_memdel((void **)&p);
}

void			free_corewar(t_corewar *war)
{
	int			i;

	i = -1;
	ft_memdel((void **)&war->arena);
	while (++i < war->nbr_fighters)
	{
		ft_memdel((void **)&war->players[i].data_file);
	}
	free_process(war->all_process);
	ft_memdel((void **)&war);
}

int				main(int argc, char **argv)
{
	t_corewar	*war;
	t_visu		*visu;

	if (argc < 2 || !(war = (t_corewar *)ft_memalloc(sizeof(t_corewar))))
		return (1);
	if (!(visu = (t_visu *)ft_memalloc(sizeof(t_visu))))
		return (1);
	ft_memset(g_coords, 0, sizeof(g_coords));
	init_struct(visu);
	border_maker(visu);
	war->arena = ft_get_arena();
	get_id(argv);
	Parsing(war, argc, argv);
	ft_init_process(war);
	get_corewar(war);
	get_visu(visu);
	ft_loop();
	// free_corewar(war);
	endwin();
	return (0);
}
