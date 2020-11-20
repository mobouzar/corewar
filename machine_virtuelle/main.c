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

	if (argc < 2 || !(war = (t_corewar *)malloc(sizeof(t_corewar))))
		return (1);
	ft_memset((void *)war, 0, sizeof(t_corewar));
	war->arena = ft_get_arena();
	get_id(argv);
	Parsing(war, argc, argv);
	ft_init_process(war);
	get_struct(war);
	ft_loop();
	free_corewar(war);
	return (0);
}
