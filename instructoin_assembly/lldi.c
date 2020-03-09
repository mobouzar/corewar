/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 15:04:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 14:55:52 by yelazrak         ###   ########.fr       */
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
    if (((d & (0b00010000)) == 0b00010000))
    {
        ft_memcpy((void *)&r, (void *)&war->arena[p], 1);
        (*arg) = hex(addr_to_hex(&r, 1));
        return (1);
    }
    if (((d & (0b00110000)) == 0b00110000))
    {
        ft_memcpy((void *)&indir, (void *)&war->arena[p], 2);
        (*arg) = hex(addr_to_hex(&indir, 2));
        return (2);
    }
    if (((d & (0b00100000)) == 0b00100000))
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
    if (((d & (0b01000000)) == 0b01000000))
    {
        ft_memcpy((void *)&r, (void *)&war->arena[p], 1);
        (*arg) = hex(addr_to_hex(&r, 1));
        return (1);
    }
    if (((d & (0b11000000)) == 0b11000000))
    {
        ft_memcpy((void *)&indir, (void *)&war->arena[p ], 2);
        (*arg) = hex(addr_to_hex(&indir, 2));
        (*arg) = (*arg) % IDX_MOD;
        ft_memcpy((void *)&dir, (void *)&war->arena[p - 2 + (*arg)], 4); 
        (*arg) = hex(addr_to_hex(&dir, 4));      
        return (2);
    }
    if (((d & (0b10000000)) == 0b10000000))
    {
        ft_memcpy((void *)&dir, (void *)&war->arena[p], 4);
        (*arg) = hex(addr_to_hex(&dir, 4));
        return (4);
    }
    return (0);
}


int get_flag_3(char_t d, int *arg, int p)
{
    t_corewar *war;
    char_t r;
    size_t dir;
    unsigned short indir;

    war = get_struct(0);
    if (((d & (0b00000100)) == 0b00000100))
    {
        ft_memcpy((void *)&r, (void *)&war->arena[p], 1);
        (*arg) = hex(addr_to_hex(&r, 1));
        return (1);
    }
    if (((d & (0b00001100)) == 0b00001100))
    {
        ft_memcpy((void *)&indir, (void *)&war->arena[p ], 2);
        (*arg) = hex(addr_to_hex(&indir, 2));
        (*arg) = (*arg) % IDX_MOD;
        ft_memcpy((void *)&dir, (void *)&war->arena[p - 2 + (*arg)], 4); 
        (*arg) = hex(addr_to_hex(&dir, 4));      
        return (2);
    }
    if (((d & (0b00001000)) == 0b00001000))
    {
        ft_memcpy((void *)&dir, (void *)&war->arena[p], 4);
        (*arg) = hex(addr_to_hex(&dir, 4));
        return (4);
    }
    return (0);
}

int lldi(t_process *p)
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
   
    i = get_flag_1(d, &arg1,p->pc + 2);
    i = get_flag_2(d, &arg2,p->pc + 2 + i);
     ft_memcpy((void *)&r, (void *)&war->arena[p->pc + 2 + i], 1);
    i = p->pc + (arg1 + arg2);
    ft_memcpy((void *)&war->arena[p->pc + i],(void *)&r, 1);
}