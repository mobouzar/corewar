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

/**
 * *
 * *
 * *
 **/

// int         set_live(unsigned int byt)
// {
//     int i;
//     unsigned int id[4] = {0xffffffff,  0xfffffffe,0xfffffffd, 0xfffffffc};
//     unsigned int value;

//     i = 0;
//     value = ft_sign(byt, 4); // addr_to_hex(&dir ,4);
//     while (i < 4)
//     {
//         if (id[i] == value)
//             return (i);
//         i++;
//     }
//     return (-1);
// }

int ft_live(t_process *p)
{
    t_corewar *war;
    unsigned int data;
    int id;

    
    war = get_struct(0);
    ft_memcpy((void *)&data, (void*)&war->arena[p->pc + 1], 4);//// curculir
    p->is_live_more = 1;
    war->nbr_live++;
    id = -1 * ft_sign(data , 4);
    if (id > 0  && id < 5)
	{ 
       
        war->players[id  -1].last_cycle_to_live = war->cycle;
        (war->players[id - 1].count_live)++;
	}
    p->pc += 5;
	// ft_putendl("ft_live_end\n");
	return (0);
}
