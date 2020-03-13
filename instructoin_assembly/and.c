/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:06:38 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

unsigned int shift_byte(char_t d, int *len, t_process *p, int *status, int pos, int shift, int s_dir)
{
	t_corewar *war;
	char_t r;
	unsigned int dir;
	unsigned short indir;

	war = get_struct(0);
	*status = 0;
	if (((d >> shift) & 0x03) == 0x03)
	{
		ft_memcpy((void *)&indir, (void *)&war->arena[pos], 2);
		(*len) += 2;
		shift = ft_sign(indir, 2);
		pos = ldi_cpy(p, shift);
		// printf("zz = %d     bbb = %s  \n",shift,addr_to_hex(&pos,4));
		return (ldi_cpy(p, shift));
	}
	if (((d >> shift) & T_REG) == T_REG)
	{
		ft_memcpy((void *)&r, (void *)&war->arena[pos], 1);
		if ((pos = read_regster(pos, war)) == -1)
		{
			*status = 1;
			return (-1);
		}
		(*len) += 1;
		return (p->regster[pos - 1]);
	}
	if (((d >> shift) & T_DIR) == T_DIR)
	{
		if (s_dir == 2)
			ft_memcpy((void *)&dir, (void *)&war->arena[pos], 2);
		else
			ft_memcpy((void *)&dir, (void *)&war->arena[pos], 4);
		(*len) += s_dir;
		return (dir);
	}
	*status = 1;
	return (0);
}

int ft_and(t_process *p)
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
	len1 = ((shift_byte(d, &len, p, &ret, p->pc + len, 6, 4)) & (shift_byte(d, &len, p, &ret, p->pc + len, 4, 4)));
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
