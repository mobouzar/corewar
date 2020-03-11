/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 13:07:19 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/11 20:48:52 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"
 
unsigned int ldi_cpy(t_process *p, int size)
{
	unsigned int stock = 0;
	t_corewar *war;

	war = get_struct(0);
	size = overrided_pos(size);
	if ((size + 4) >= MEM_SIZE)/////khatae
	{
		ft_memcpy((void *)&stock  , (void *)&war->arena[p->pc + size], (MEM_SIZE - size));
		ft_memcpy((void *)&stock + (MEM_SIZE - size), (void *)&war->arena[0], 4 - (MEM_SIZE - size));
	}
	else
		ft_memcpy((void *)&stock, (void *)&war->arena[p->pc + size], 4);
		//  printf("ooo = %d\n",ft_sign(stock,4));
	return (stock);
}

 int shift_data(char_t d, int *len, t_process *p, int *status, int pos, int shift, int s_dir)
{
	t_corewar *war;
	char_t r;
	size_t dir;
	unsigned short indir;

	war = get_struct(0);
	*status = 0;
	if (((d >> shift) & 0x03) == 0x03)
	{
		ft_memcpy((void *)&indir, (void *)&war->arena[pos], 2);
		(*len) += 2;
		 shift = ft_sign(indir, 2);
		
		return (ft_sign(ldi_cpy(p,  shift),4));
	}
	if (((d >> shift) & T_REG) == T_REG)
	{
		// ft_putendl("\n\nrrrrrr\n");
		ft_memcpy((void *)&r, (void *)&war->arena[pos], 1);
		//f("pos00000 = %d\n", pos);
		if ((pos = read_regster(pos, war)) == -1)
		{
			//f("pos = %d\n", pos);
			*status = 1;
			return (-1);
		}
		(*len) += 1;
		//f("hh pos= %d\n",pos);
		return (ft_sign(p->regster[pos - 1],4));
	}
	if (((d >> shift) & T_DIR) == T_DIR)
	{
		// ft_putendl("dakhlat");
		if (s_dir == 2)
			ft_memcpy((void *)&dir, (void *)&war->arena[pos], 2);
		else
			ft_memcpy((void *)&dir, (void *)&war->arena[pos], 4);
		(*len) += s_dir;
		//f("dir =====> %s\n", addr_to_hex(&dir, 2));
		return (ft_sign(dir,s_dir));
	}
	*status = 1;
	return (0);
}

int ft_ldi(t_process *p)
{
	t_corewar *war;
	char_t d;
	int len1;
	int len;
	int r;
	int i;
	int ret =0;

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
	{
		return (r + 1);
	}
	cpy_arena_to_reg(war, p, (len1 % IDX_MOD), ret);
	return (r + 1);
}












































































// unsigned int shift_data(char_t d, t_process *p, int *status, int shift, int s_dir)
// {
// 	t_corewar *war;
// 	char_t r;
// 	size_t dir;
// 	unsigned short indir;

// 	war = get_struct(0);
// 	status = 0;
// 	if (((d >> shift) & 0x03) == 0x03)
// 	{
// 		ft_memcpy((void *)&indir, (void *)&war->arena[p->pc], 2);
// 		p->pc += ft_sign(indir, 2);
// 		return (ldi_cpy(p, p->pc));
// 	}
// 	if (((d >> shift) & T_REG) == T_REG)
// 	{
// 		ft_memcpy((void *)&r, (void *)&war->arena[p->pc], 1);
// 		if ((indir = read_regster(p->pc, war)) == -1)
// 		{
// 			*status = 1;
// 			return (-1);
// 		}
// 		p->pc += 2;
// 		return (p->regster[indir - 1]);
// 	}
// 	if (((d >> shift) & T_DIR) == T_DIR)
// 	{
// 		if (s_dir == 2)
// 			ft_memcpy((void *)&dir, (void *)&war->arena[p->pc], 2);
// 		else
// 			ft_memcpy((void *)&dir, (void *)&war->arena[p->pc], 4);
// 		p->pc += s_dir;
// 		return (dir);
// 	}
// 	*status = 1;
// 	return (0);
// }

// int ft_ldi(t_process *p)
// {
// 	t_corewar *war;
// 	char_t d;
// 	unsigned int len1;
// 	int r;
// 	int i;
// 	int ret;

// 	war = get_struct(0);
// 	i = 6;
// 	ft_memcpy((void *)&d, (void *)&war->arena[++p->pc], 1);
// 	if ((r = get_size_of_flag(d, hex(addr_to_hex(&war->arena[p->pc - 1], 1)), &ret)) && ret == 1)
// 		return (r + 1);
// 	while (i >= 4)
// 	{
// 		len1 += ft_sign(shift_data(d, p, &ret, i, 4), 4);
// 		if (ret == 1)
// 			return (r);
// 		i -= 2;
// 	}
// 	if ((d = read_regster(p->pc, war)) == -1)
// 		return (r + 1);
// 	cpy_arena_to_reg(war, p, len1 % IDX_MOD, d);
// 	return (r + 1);
// }