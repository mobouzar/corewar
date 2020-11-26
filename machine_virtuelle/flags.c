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

static	int		manage_file(t_corewar *war, int id, char *file_name)
{
	t_header	*lst;
	int			n;

	if ((id = get_id_player(id, 1)) < 0 || !file_name)
		return (0);
	n = ft_strlen(file_name);
	if (n < 5 || ft_strcmp(file_name + (n - 4), ".cor"))
		return (0);
	if (!(lst = ft_cin_file(file_name)))
		return (0);
	war->players[id - 1].data_file = lst;
	war->nbr_fighters++;
	return (1);
}

void			adaptation_player(t_corewar *war)
{
	int			i;
	int			j;
	int			perv;

	i = -1;
	while (++i < 3)
	{
		if (!war->players[i].data_file)
		{
			j = i;
			perv = i;
			while (++j < 4)
			{
				if (war->players[j].data_file)
				{
					war->players[perv].data_file =
					war->players[j].data_file;
					war->players[j].data_file = NULL;
					perv++;
				}
			}
		}
	}
}

int				ft_copy_player_arena(t_corewar *war)
{
	t_header	*lst;
	int			i;
	int			position;
	int			pa;

	i = -1;
	if (!war->nbr_fighters)
		return (0);
	pa = 4096 / war->nbr_fighters;
	position = 0;
	adaptation_player(war);
	while (++i < war->nbr_fighters)
	{
		lst = war->players[i].data_file;
		if (lst)
			ft_memcpy(&war->arena[position], lst->champ,
			hex(addr_to_hex(&lst->prog_size, 4)));
		war->players[i].Starting_point = position;
		position += pa;
	}
	return (1);
}

static	int		task_parsing(t_corewar *war, int i, char **argv)
{
	if (argv[i] && !ft_strcmp(argv[i], "-v"))
	{
		war->v = 1;
	}
	else if (!ft_strcmp(argv[i], "-dump"))
	{
		if (!is_int(war, argv[++i]))
			return (0);
	}
	return (i);
}

int				parsing(t_corewar *war, int argc, char **argv)
{
	int			i;
	int			index;

	i = 0;
	while (++i < argc)
	{
		if (!ft_strcmp(argv[i], "-v") || !ft_strcmp(argv[i], "-dump"))
		{
			if ((i = task_parsing(war, i, argv)) == 0)
				return (0);
		}
		else if (!ft_strcmp(argv[i], "-n"))
		{
			if (!argv[++i])
				return (0);
			index = ft_atoi(argv[i]);
			if (!(index > 0 && index < 5) ||
				!manage_file(war, index, argv[++i]))
				return (0);
		}
		else if (!manage_file(war, -1, argv[i]))
			return (0);
	}
	return (ft_copy_player_arena(war));
}
