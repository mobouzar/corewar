/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/11 20:12:51 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

// int ft_lldi(t_process *p)
// {
//     t_corewar *war;
//     char_t r;
//     char_t d;
//     unsigned int arg1;
//     unsigned int arg2;
//     int i;

//     war = get_struct(0);
//     ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], 1);
   
//     i = get_flag_1(d, &arg1,p->pc + 2);
//     i = get_flag_2(d, &arg2,p->pc + 2 + i);
//      ft_memcpy((void *)&r, (void *)&war->arena[p->pc + 2 + i], 1);
//     i = p->pc + (arg1 + arg2);
//     ft_memcpy((void *)&war->arena[p->pc + i],(void *)&r, 1);
// 	return (1);
// }

int ft_lldi(t_process *p)
{
	t_corewar *war;
	char_t d;
	int len1;
	int len;
	int r;
	int i;
	int ret = 0;

	war = get_struct(0);
	len = p->pc + 2;
	len1 = 0;
	i = 6;
	ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], 1);
	if ((r = get_size_of_flag(d, hex(addr_to_hex(&war->arena[p->pc], 1)), &ret)) && ret == 1)
		return (r + 1);
	while (i >= 4)
	{
		len1 += shift_data(d, &len, p, &ret, p->pc + len, i, 2);
		if (ret == 1)
			return (r);
		i -= 2;
	}
	if ((ret = read_regster(len, war)) == -1)
		return (r + 1);
	cpy_arena_to_reg(war, p, (len1), ret);
	return (r + 1);
}