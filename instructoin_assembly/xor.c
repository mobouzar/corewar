/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 18:28:41 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"




int xor(t_process *p)
{
    t_corewar *war;
    char_t r;
    char_t d;
    unsigned int arg1;
    unsigned int arg2;
    unsigned int i;

    war = get_struct(0);
    ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], 1);
    i = get_flag_1(d, &arg1,p->pc + 2);
    i = get_flag_2(d, &arg2,p->pc + 2 + i);
    ft_memcpy((void *)&r, (void *)&war->arena[p->pc + 2 + i], 1);
    arg1 = (arg1 ^ arg2);
    ft_memcpy((void *)&p->regster[r],(void *)&arg1, 1);
    return (i);
}