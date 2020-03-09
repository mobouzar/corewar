/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 19:04:01 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int get_flag_2(char_t d, int *arg, int p)
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
        return (1);
    }
   if ((((4>>d) & (0b00000011)) == 0b00000011))
    {
         ft_memcpy((void *)&indir, (void *)&war->arena[p ], 2);
        (*arg) = hex(addr_to_hex(&indir, 2));
        (*arg) = (*arg) % IDX_MOD;
        ft_memcpy((void *)&dir, (void *)&war->arena[p - 2 + (*arg)], 4); 
        (*arg) = hex(addr_to_hex(&dir, 4));      
        return (2);
    }
    if ((((4>>d) & (0b00000010)) == 0b00000010))
    {
        ft_memcpy((void *)&dir, (void *)&war->arena[p], 4);
        (*arg) = hex(addr_to_hex(&dir, 4));
        return (4);
    }
    return (0);
}


int get_flag_1(char_t d, int *arg, int p)
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
        return (1);
    }
    if ((((6>>d) & (0b00000011)) == 0b00000011))
    {
         ft_memcpy((void *)&indir, (void *)&war->arena[p ], 2);
        (*arg) = hex(addr_to_hex(&indir, 2));
        (*arg) = (*arg) % IDX_MOD;
        ft_memcpy((void *)&dir, (void *)&war->arena[p - 2 + (*arg)], 4); 
        (*arg) = hex(addr_to_hex(&dir, 4));      
        return (2);
    }
    if ((((6>>d) & (0b00000010)) == 0b00000010))
    {
        ft_memcpy((void *)&dir, (void *)&war->arena[p], 4);
        (*arg) = hex(addr_to_hex(&dir, 4));
        return (4);
    }
    return (0);
}


int get_flag_3(char_t d, int *arg, int p)
{
    char_t r;
    t_corewar *war;
    size_t dir;
    unsigned short indir;

    war = get_struct(0);
    if ((((2>>d) & (0b00000001)) == 0b00000001))
    {
        ft_memcpy((void *)&r, (void *)&war->arena[p], 1);
        (*arg) = hex(addr_to_hex(&r, 1));
        return (1);
    }
    if ((((2>>d) & (0b00000011)) == 0b00000011))
    {
        ft_memcpy((void *)&indir, (void *)&war->arena[p ], 2);
        (*arg) = hex(addr_to_hex(&indir, 2));
        (*arg) = (*arg) % IDX_MOD;
        ft_memcpy((void *)&dir, (void *)&war->arena[p - 2 + (*arg)], 4); 
        (*arg) = hex(addr_to_hex(&dir, 4));      
        return (2);
    }
    if ((((2 >>d) & (0b00000010)) == 0b00000010))
    {
        ft_memcpy((void *)&dir, (void *)&war->arena[p], 4);
        (*arg) = hex(addr_to_hex(&dir, 4));
        return (4);
    }
    return (0);
}

int sti(t_process *p)
{
    t_corewar *war;
    char_t r;
    char_t d;
    int arg1;
    int arg2;
    int i;
    size_t dir1;
    unsigned short indir;

    war = get_struct(0);
    ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], 1);
    ft_memcpy((void *)&r, (void *)&war->arena[p->pc + 2], 1);
    i = get_flag_2(d, &arg1,p->pc + 2);
    i = get_flag_3(d, &arg2,p->pc + 2 + i);
    i = p->pc + (arg1 + arg2) % IDX_MOD;
    ft_memcpy((void *)&war->arena[p->pc + i],(void *)&r, 1);

}