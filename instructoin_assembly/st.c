/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/09 18:16:46 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int st(t_process *p)
{
    t_corewar *war;
    char_t d;
    char_t  r;
    unsigned short indir;

    war = get_struct(0);
    ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], sizeof(char_t));
     ft_memcpy((void *)&r, (void *)&war->arena[p->pc + 2], sizeof(char_t));
    if ((d & (4 << 6)) == d)
    {
        ft_memcpy((void *)&indir, (void *)&war->arena[p->pc + 2], sizeof(unsigned short));
        indir = ft_sign(indir,2);
        ft_memcpy((void *)&war->arena[p->pc + indir % IDX_MOD],(void *)&p->regster[hex(addr_to_hex(r, 1)) - 1], 4);
    }
    else
    {
        ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 2], sizeof(char_t));
        ft_memcpy((void *)&p->regster[hex(addr_to_hex(d, 1)) - 1], (void *)&p->regster[hex(addr_to_hex(r, 1)) - 1], 4);
    }
    p->carry = 0;
    if (!p->regster[hex(addr_to_hex(r, 1)) - 1])
        p->carry = 1;
    return (0);
}