/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 15:16:05 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"


int      add(t_process *p)
{
    t_corewar *war;
    char_t r1;
    char_t r2;
    char_t r3;

    war = get_struct(0);
    ft_memcpy((void *)&r1, (void *)&war->arena[p->pc + 1], 1);
    ft_memcpy((void *)&r2, (void *)&war->arena[p->pc + 2], 1);
    ft_memcpy((void *)&r3, (void *)&war->arena[p->pc + 3], 1);
    r1 = hex(addr_to_hex(&r1,1));
    r2 = hex(addr_to_hex(&r2,1));
    r3 = hex(addr_to_hex(&r3,1));
    p->regster[r3] = p->regster[r1] + p->regster[r2];
    p->carry = 0;
    if (!(p->regster[r3]))
      p->carry = 1;
    return (3);
}