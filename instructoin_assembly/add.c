/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/11 22:32:08 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"


// int     ft_add(t_process *p)
// {
//     t_corewar *war;
//     char_t r1;
//     char_t r2;
//     char_t r3;

//     war = get_struct(0);
//     ft_memcpy((void *)&r1, (void *)&war->arena[p->pc + 1], 1);
//     ft_memcpy((void *)&r2, (void *)&war->arena[p->pc + 2], 1);
//     ft_memcpy((void *)&r3, (void *)&war->arena[p->pc + 3], 1);
//     r1 = hex(addr_to_hex(&r1,1));
//     r2 = hex(addr_to_hex(&r2,1));
//     r3 = hex(addr_to_hex(&r3,1));
//     p->regster[r3] = p->regster[r1] + p->regster[r2];
//     p->carry = 0;
//     if (!(p->regster[r3]))
//       p->carry = 1;
//     return (3);
// }

int     ft_add(t_process *p)
{
	t_corewar *war;
	char_t d;
	unsigned int len1;
	int len;
	int r;
	int ret = 0;

	war = get_struct(0);
	len = p->pc + 2;
	len1 = 0;
	ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], 1);
	if ((r = get_size_of_flag(d, hex(addr_to_hex(&war->arena[p->pc], 1)), &ret)) && ret == 1)
		return (r + 1);
	len1 = ((shift_byte(d, &len, p, &ret, p->pc + len, 6, 4)) + (shift_byte(d, &len, p, &ret, p->pc + len, 4, 4)));
	if (ret == 1)
		return (r);
	if ((ret = read_regster(len, war)) == -1)
		return (r + 1);
	ft_memcpy(&p->regster[ret - 1],&len1,4);
	p->carry = 0;
    if (!(p->regster[ret - 1]))
    p->carry = 1;
	return (r + 1);
}