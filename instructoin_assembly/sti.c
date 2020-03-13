/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:08:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int ft_sti(t_process *p)
{
	t_corewar *war;
	char_t d;
	int len1;
	int len;
	int r;
	int i;
	int ret =0;

	war = get_struct(0);
	len = p->pc + 3;
	len1 = 0;
	i = 4;
	ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], 1);
	if ((r = get_size_of_flag(d, hex(addr_to_hex(&war->arena[p->pc], 1)), &ret)) && ret == 1)
		return (r + 1);
	while (i >= 2)
	{
		len1 += shift_data(d, &len, p, &ret,len, i, 2);
		// printf("lll = %d\n",len1);
		if (ret == 1)
			return (r);
		i -= 2;
	}
	if ((ret = read_regster(p->pc + 2, war)) == -1)
		return (r + 1);
	// printf("xx = %d\n", ret);
	cpy_reg_to_arena(war, p, (len1 % IDX_MOD), ret);
	return (r + 1);
}
