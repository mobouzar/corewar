/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 14:53:52 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"





int lld(t_process *p)
{
    t_corewar *war;
    char_t d;
    unsigned short indir;
    unsigned int dir;
    int i;

    war = get_struct(0);
    ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], sizeof(char_t));
    if ((d & (4 << 6)) == d)
    {
        ft_memcpy((void *)&indir, (void *)&war->arena[p->pc + 2], sizeof(unsigned short));
        indir = ft_sign((size_t)indir, 2);
        ft_memcpy((void *)&dir, (void *)&war->arena[p->pc + indir % IDX_MOD], sizeof(unsigned int));
        ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 4], sizeof(char_t));
    }
    else
    {
        ft_memcpy((void *)&dir, (void *)&war->arena[p->pc + 2], sizeof(unsigned int));
        ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 6], sizeof(char_t));
    }
    ft_memcpy((void *)&p->regster[hex(addr_to_hex(d, 1)) - 1], (void *)&dir, sizeof(size_t));
    p->carry = 0;
    if (!p->regster[hex(addr_to_hex(d, 1)) - 1])
        p->carry = 1;
    return (0);
}