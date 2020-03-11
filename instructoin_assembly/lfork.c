/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lfork.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/10 11:56:33 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int   ft_lfork(t_process *p)
{
    unsigned int dir;
    t_corewar *war;
    t_process *new;

    war = get_struct(0);
    ft_memcpy((void *)&dir, (void *)&war->arena[p->pc + 1], sizeof(size_t));
    if (!(new = (t_process *)malloc(sizeof(t_process))))
        return (1);
    ft_memset((void *)new, 0, sizeof(t_process));
    ft_memcpy((void *)new, (void *)p, sizeof(t_process));
    new->pc += hex(addr_to_hex(&dir,4));
    new->next = war->players[p->id - 1].process;
    war->players[p->id - 1].process = new;
	return (1);
}

