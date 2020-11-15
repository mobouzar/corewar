/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/10 16:02:46 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int ft_live(t_process *p)
{
    t_corewar *war;
    unsigned int data;
    int id;

    
    war = get_struct(0);
    ft_memcpy((void *)&data, (void*)&war->arena[p->pc + 1], 4);
    p->is_live_more = 1;
    war->nbr_live++;
    id = -1 * ft_sign(data , 4);
    if (id > 0  && id < 5 && ft_sign(data , 4) == (int)p->regster[0])
	{     
        war->players[id  - 1].last_cycle_to_live = war->cycle;
        (war->players[id - 1].count_live)++;
	}
    p->pc += 5;
	return (0);
}
