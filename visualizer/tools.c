/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:06:05 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/24 12:09:45 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void	get_winner(t_corewar *war, t_visu *visu)
{
	int	last_live;
	int	i;

	i = 0;
	last_live = 0;
	visu->last_live_color = BORDER_COLOR;
	while (i < 4)
	{
		if (last_live < war->players[i].last_cycle_to_live)
		{
			last_live = war->players[i].last_cycle_to_live;
			visu->last_live_color = i + 5;
		}
		// dprintf(2, "id => |%d|, last_live => |%d|\n", i, war->players[i].last_cycle_to_live);
		i++;
	}
	border_maker(visu);
	wrefresh(visu->arena);
}