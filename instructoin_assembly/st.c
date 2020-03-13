/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/12 22:07:03 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

const t_op op_tab1[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR + T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND + T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG + T_DIR + T_IND, T_REG + T_IND + T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG + T_IND + T_DIR, T_REG + T_IND + T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 + r2 -> r3", 1, 0},
	{"xor", 3, {T_REG + T_IND + T_DIR, T_REG + T_IND + T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG + T_DIR + T_IND, T_DIR + T_REG, T_REG}, 10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG + T_DIR + T_IND, T_DIR + T_REG}, 11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR + T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG + T_DIR + T_IND, T_DIR + T_REG, T_REG}, 14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

static int check(char_t d, int index, int pos, int *state)
{
	*state = 0;

	if ((d & 3) == 3)
	{
		if (op_tab1[index].args[pos] == 4 || op_tab1[index].args[pos] == 5 ||
			op_tab1[index].args[pos] == 6 || op_tab1[index].args[pos] == 7)
			*state = 0;
		else
			*state = 1;
		return (2);
	}
	if ((d & T_REG) == T_REG)
	{
		if (op_tab1[index].args[pos] == 1 || op_tab1[index].args[pos] == 5 ||
			op_tab1[index].args[pos] == 3 || op_tab1[index].args[pos] == 7)
			*state = 0;
		else
			*state = 1;
		return (1);
	}
	if ((d & T_DIR) == T_DIR)
	{
		if (op_tab1[index].args[pos] == 2 || op_tab1[index].args[pos] == 3 ||
			op_tab1[index].args[pos] == 6 || op_tab1[index].args[pos] == 7)
		{
			*state = 0;
			if (op_tab1[index].size2_dir == 0)
				return (4);
			else
				return (2);
		}
		else
		{
			*state = 1;
			if (op_tab1[index].size2_dir == 0)
				return (4);
			else
				return (2);
		}
	}
	*state = 1;
	return (0);
}

int get_size_of_flag(char_t d, int index, int *ret)
{
	int count;
	int state;
	int i;
	int j;

	count = 0;
	i = 6;
	j = -1;
	state = 0;
	*ret = 0;
	while (i >= 2 && ++j < 3 && j < op_tab1[index - 1].nbr_args)
	{
		count += check(((d >> i) & (0x03)), index - 1, j, &state);
		if (state == 1 || (((d << 6) & (0xff)) != 0))
			*ret = 1;
		i -= 2;
	}
	return (count);
}

int overrided_pos(int pos)
{
	if (pos >= 0)
		return (pos % IDX_MOD);
	else
	{
		if (pos < IDX_MOD)
			return (MEM_SIZE + pos);
		else
			return (MEM_SIZE - (pos % IDX_MOD));
	}
	return (0);
}

void cpy_reg_to_arena(t_corewar *war, t_process *p, int size, char_t r)
{
	size = overrided_pos( p->pc + size);
	size = size % MEM_SIZE; 
	// printf("kkkk = %d				ss=%d\n",r,hex(addr_to_hex(&p->regster[0], 4)));
	if (size + 4 > MEM_SIZE)
	{
		ft_memcpy((void *)&war->arena[size], (void *)&p->regster[r - 1], (MEM_SIZE - size));
		ft_memcpy((void *)&war->arena[0], (void *)&p->regster[r - 1], 4 - (MEM_SIZE - size));
	}
	else
		ft_memcpy((void *)&war->arena[size], (void *)&p->regster[r - 1], 4);
}

int ft_st(t_process *p)
{
	t_corewar *war;
	unsigned short indir;
	char_t d;
	char_t r;
	int ret;

	war = get_struct(0);
	ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 1], sizeof(char_t));
	if ((r = get_size_of_flag(d, hex(addr_to_hex(&war->arena[p->pc], 1)), &ret)) && ret == 1)
		return (r + 1);
	ret = r;
	ft_memcpy((void *)&r, (void *)&war->arena[p->pc + 2], sizeof(char_t));
	if (((d >> 4) & (0x03)) == 3)
	{
		ft_memcpy((void *)&indir, (void *)&war->arena[p->pc + 3], sizeof(unsigned short));
		cpy_reg_to_arena(war, p, ft_sign(indir, 2) % IDX_MOD, r);
	}
	else
	{
		ft_memcpy((void *)&d, (void *)&war->arena[p->pc + 3], sizeof(char_t));
		ft_memcpy((void *)&p->regster[hex(addr_to_hex(&d, 1)) - 1], (void *)&p->regster[hex(addr_to_hex(&r, 1)) - 1], 4);
	}
	p->carry = 0;
	if (!p->regster[hex(addr_to_hex(&r, 1)) - 1])
		p->carry = 1;
	return (ret + 1);
}