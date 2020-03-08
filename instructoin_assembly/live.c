/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/08 18:29:53 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"


int         set_live(size_t dir)
{
    int i;
    const char *id[4] = {"ffffffff",  "fffffffe","fffffffd", "fffffffc"};
    char            *value;

    i = 0;
    value = addr_to_hex(&dir ,4);
    while (i < 4)
    {
        if (!ft_strcmp(value,id[i]))
            return (i + 1);
        i++;
    }
    return (-1);
}

int live(t_process *p)
{
    t_corewar *war;
    size_t    dir;
    int id;

    war = get_struct(0);
    p->nbr_cycler_live = war->cycle;
    ft_memcpy((void *)&dir, (void*)war->arena[p->pc], sizeof(size_t));
    if ((id = set_live(dir)) > 0)
        war->players[id]->live++;
}
