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

int main(int argc, char **argv)
{

	(void)argc;
	(void)argv;

	// t_header *lst;
	t_corewar *war;

	if (!(war = (t_corewar *)malloc(sizeof(t_corewar))))
		return (1);
	ft_memset((void *)war, 0, sizeof(t_corewar));
	// war->nbr_fighters = argc - 1;
	// ft_init_process(war);
	// lst =  ft_cin_file(argv[1]);
	// war->arena = ft_get_arena();
	manage(war, argc, argv);
	get_struct(war);
	// printf("\n\nsize == %d\n", hex(addr_to_hex(&lst->prog_size,4)));
	// ft_memcpy(&war->arena[0], lst->champ, hex(addr_to_hex(&lst->prog_size,4)));
	ft_loop();
	// ft_print_arena();

	return (0);
}