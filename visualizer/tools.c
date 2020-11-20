/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:06:05 by mobouzar          #+#    #+#             */
/*   Updated: 2020/11/20 16:51:18 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

void    print_reg_in_arena(int cursor0, int size)
{
	int			i;
    t_corewar   *war;
    t_visu      *visu;

	i = 0;
    war = get_corewar(0);
    visu = get_visu(0);
    size = overrided_pos(size, cursor0);
    wattron(visu->arena, visu->color);
	while (i < 4)
	{
    	print_byte(&war->arena[size], visu, visu->coords[size].y, visu->coords[size].x);
		size++;
		i++;
	}
    wattroff(visu->arena, visu->color);
    wrefresh(visu->arena);
}