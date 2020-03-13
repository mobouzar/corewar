/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:06:50 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int read_regster(int p, t_corewar *war)
{
	char_t r;
	int i;

	ft_memcpy((void *)&r, (void *)&war->arena[p], sizeof(char_t));
	i = hex(addr_to_hex(&r, 1));
	if (i > 0 && i <= 16)
		return (i);
	// printf("ff= %d    i i  = %d\n", p,i);
	return (-1);
}

void cpy_arena_to_reg(t_corewar *war, t_process *p, int size, char_t r)
{

	size = overrided_pos(p->pc + size);
	// printf("mmm = %d\n", size);
	if (size + 4 > MEM_SIZE)
	{
		ft_memcpy((void *)&p->regster[r - 1], (void *)&war->arena[size], (MEM_SIZE - size));
		ft_memcpy((void *)&p->regster[r - 1] + (MEM_SIZE - size), (void *)&war->arena[0], 4 - (MEM_SIZE - size));
	}
	else
	{
		ft_memcpy((void *)&p->regster[r - 1], (void *)&war->arena[size], 4);
		// printf("aa = %s\n",addr_to_hex(&p->regster[r - 1],4));
	}
	
}

// int ft_ld(t_process *p)
// {
// 	t_corewar *war;
// 	char_t d;
// 	unsigned short indir;
// 	unsigned int dir;
// 	int ret;
// 	int r;

// 	war = get_struct(0);
// 	ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], sizeof(char_t));
// 	if ((r = get_size_of_flag(d, hex(addr_to_hex(&war->arena[p->pc], 1)), &ret)) && ret == 1)
// 		return (r + 1);
// 	if (((d >> 6) & (0x03)) == 3)
// 	{
// 		ft_memcpy((void *)&indir, (void *)&war->arena[p->pc + 2], sizeof(unsigned short));
// 		if ((ret = read_regster(p->pc + 4, war)) && ret == -1)
// 			return (r + 1);
// 		cpy_arena_to_reg(war, p, ft_sign((size_t)indir, 2), ret);
// 	}
// 	else
// 	{
// 		ft_memcpy((void *)&dir, (void *)&war->arena[p->pc + 2], sizeof(unsigned int));
// 		if ((ret = read_regster(p->pc + 6, war)) && ret == -1)
// 			return (r + 1);
// 		ft_memcpy((void *)&p->regster[ret - 1], (void *)&dir, sizeof(size_t));
// 	}

// 	p->carry = 0;
// 	if (!p->regster[hex(addr_to_hex(&d, 1)) - 1])
// 		p->carry = 1;
// 	return (r + 1);
// }

int ft_ld(t_process *p)
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
	len1 = shift_byte(d, &len, p, &ret,len, 6, 4);
	if (ret == 1)
		return (r);
	if ((ret = read_regster(len, war)) == -1)
		return (r + 1);
	ft_memcpy(&p->regster[ret - 1], &len1,4);
	p->carry = 0;
	if (!p->regster[ret - 1])
		p->carry = 1;
	return (r + 1);
}
