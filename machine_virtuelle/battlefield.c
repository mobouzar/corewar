/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battlefield.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:04:41 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 21:50:39 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"
#include "../include/visualizer.h"

const t_op op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

void ft_exec(t_process *p, t_corewar *war)
{
	int (*func[])(t_process *) = {ft_live, ft_ld, ft_st, ft_add, ft_sub, ft_and, \
	ft_or, ft_xor, ft_zjmp, ft_ldi, ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};
	int i;

	i = hex(addr_to_hex(&war->arena[p->pc], 1));
	int a;
	// ft_putendl("ghdghghd");
	ft_memcpy(&a, &war->arena[3], 4);
	if (i >= 1 && i <= 16)
	{
		p->wait = 1;
		if (p->cycle_count == op_tab[i - 1].nbr_cycler)
		{
			// printf("register ==> %s  cycle => %d,   pc = %d  iicary = %d \n", addr_to_hex(&p->regster[2], 4), p->cycle_count,p->pc,p->carry);
			p->pc += func[i - 1](p);
			// printf("register ==> %s  cycle => %d,   pc = %d  iicary = %d \n", addr_to_hex(&p->regster[2], 4), p->cycle_count,p->pc,p->carry);
			p->cycle_count = 0;
			p->wait = 0;
		}
		p->cycle_count++;
	}
	if (!p->wait)
		p->pc++;
}

void ft_loop(void)
{
	int i;
	t_corewar *war;
	t_process *p;

	war = get_struct(0);
	// war->arena[55] = 90;
	while (++war->cycle < 100000)
	{
		i = -1;
		while (++i < war->nbr_fighters)
		{
			p = war->players[i].process;
			while (p)
			{
				//if (p->live)
				ft_exec(p, war);
				p = p->next;
			}
			
			// dprintf((fd = open("/dev/ttys003", O_RDWR)),"live = %d \n" ,war->players[i]->live);
			// close(fd);
		}
	}
	board(war);
	// ft_print_arena();
	
}