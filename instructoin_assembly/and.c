/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 18:27:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int get_flag_byte_2(char_t d, int *arg, int p, t_process *pr)
{
    t_corewar *war;
    char_t r;
    size_t dir;
    unsigned short indir;

    war = get_struct(0);
   if ((((4>>d) & (0b00000001)) == 0b00000001))
    {
         ft_memcpy((void *)&r, (void *)&war->arena[p], 1);
        (*arg) = hex(addr_to_hex(&r, 1));
        (*arg) = pr->regster[(*arg)];
        return (1);
    }
   if ((((4>>d) & (0b00000011)) == 0b00000011))
    {
         ft_memcpy((void *)&indir, (void *)&war->arena[p ], 2);
        (*arg) = hex(addr_to_hex(&indir, 2));
        (*arg) = (*arg) % IDX_MOD;
        ft_memcpy((void *)arg, (void *)&war->arena[p - 2 + (*arg)], 4);    
        return (2);
    }
    if ((((4>>d) & (0b00000010)) == 0b00000010))
    {
       ft_memcpy((void *)&arg, (void *)&war->arena[p], 4);
        return (4);
    }
    return (0);
}


int get_flag_byte_1(char_t d, int *arg, int p, t_process *pr)
{
    t_corewar *war;
    char_t r;
    size_t dir;
    unsigned short indir;

    war = get_struct(0);
    if ((((6>>d) & (0b00000001)) == 0b00000001))
    {
        ft_memcpy((void *)&r, (void *)&war->arena[p], 1);
        (*arg) = hex(addr_to_hex(&r, 1));
        (*arg) = pr->regster[(*arg)];
        return (1);
    }
    if ((((6>>d) & (0b00000011)) == 0b00000011))
    {
        ft_memcpy((void *)&indir, (void *)&war->arena[p ], 2);
        (*arg) = hex(addr_to_hex(&indir, 2));
        (*arg) = (*arg) % IDX_MOD;
        ft_memcpy((void *)arg, (void *)&war->arena[p - 2 + (*arg)], 4);  
        return (2);
    }
    if ((((6>>d) & (0b00000010)) == 0b00000010))
    {
        ft_memcpy((void *)&arg, (void *)&war->arena[p], 4);
        return (4);
    }
    return (0);
}



int and(t_process *p)
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
    arg1 = (arg1 & arg2);
    ft_memcpy((void *)&p->regster[r],(void *)&arg1, 1);
    return (i);
}