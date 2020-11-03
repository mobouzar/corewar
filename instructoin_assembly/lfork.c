/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:06:55 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int   ft_lfork(t_process *p)
{
    unsigned int byt;
    t_corewar *war;
    t_process *new;

    war = get_struct(0);
	// ft_putendl("fork");
    ft_memcpy((void *)&byt, (void *)&war->arena[p->pc + 1], 2);
    if (!(new = (t_process *)malloc(sizeof(t_process))))
        return (0);
    ft_memset(new, 0, sizeof(t_process));
    ft_memcpy(new, p, sizeof(t_process));
    war->nbr_process++;
    new->pc += ft_sign(byt,2);
    new->pc %= SIZE_MAX;
    new->next = war->players[p->id - 1].process;
    war->players[p->id - 1].process = new;
	ft_exec(new, war);
    p->pc += 3;
	return (0);
}

