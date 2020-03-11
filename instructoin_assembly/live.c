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

int         set_live(size_t dir)
{
    int i;
    const char *id[4] = {"ffffffff",  "fffffffe","fffffffd","fffffffc"};
    char            *value;

    i = 0;
    value = addr_to_hex(&dir ,4);
    while (i < 4)
    {
        if (!ft_strcmp(value,id[i]))
            return (i);
        i++;
    }
    return (-1);
}

int ft_live(t_process *p)
{
    t_corewar *war;
    size_t    dir;
    int id;

    war = get_struct(0);
	// printf("ss= %s\n",addr_to_hex(&p->regster[0] ,4));
    p->nbr_cycler_live = war->cycle;
    ft_memcpy((void *)&dir, (void*)&war->arena[p->pc + 1], sizeof(size_t));
    if ((id = set_live(dir)) >= 0)
	{
		// printf("dd = %d\n", id);
        (war->players[id].live)++;
	}	
	return (4);
}
