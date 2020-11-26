/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobouzar <mobouzar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 22:04:41 by yelazrak          #+#    #+#             */
/*   Updated: 2020/11/26 11:00:22 by mobouzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

t_op op_tab[17] =
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
	int (*func[])(t_process *) = {ft_live, ft_ld, ft_st, ft_add, ft_sub,\
		ft_and, ft_or, ft_xor, ft_zjmp, ft_ldi, ft_sti, ft_fork,\
		ft_lld, ft_lldi, ft_lfork, ft_aff};
	int i;
	p->pc %= MEM_SIZE;
	i = hex(addr_to_hex(&war->arena[p->pc], 1));
	if (i >= 1 && i <= 16)
	{
		if ((p->cycle_count) == (op_tab[i - 1].nbr_cycler - 1))
		{
			func[i - 1](p);
			p->cycle_count = 0;
		}
		else
			p->cycle_count++;
	}
	else
		p->pc++;
}

static void task_die_cursor(t_process **list_process, t_process *tmp, t_process **head)
{
	t_corewar *war;

	war = get_corewar(0);
	if (!tmp)
	{
		(*head) = (*list_process)->next;
		tmp = (*list_process);
		if (!(*list_process)->next)
			war->last_process = NULL;
		(*list_process) = (*list_process)->next;
		ft_memdel((void **)&tmp);
	}
	else
	{
		tmp->next = (*list_process)->next;
		if (!(*list_process)->next)
			war->last_process = tmp;
		ft_memdel((void **)list_process);
		(*list_process) = tmp->next;
	}
}

t_process *die_cursor(t_corewar *war, t_process *list_process)
{
	t_process *head;
	t_process *tmp;

	tmp = NULL;
	head = list_process;
	while (list_process)
	{
		if (list_process->is_live_more == 0)
		{
			war->nbr_process--;
			task_die_cursor(&list_process, tmp, &head);
		}
		else
		{
			list_process->is_live_more = 0;
			tmp = list_process;
			list_process = list_process->next;
		}
	}
	return head;
}



static void ft_Controlle(t_corewar *war)
{
	int i;

	i = -1;
	war->all_process = die_cursor(war, war->all_process);
	while (++i < war->nbr_fighters)
		war->players[i].count_live = 0;
	if (war->nbr_live >= NBR_LIVE || war->nbr_checks == 9)
	{
		war->cycle_to_die -= 50;
		war->nbr_checks = 0;
	}
	else
		war->nbr_checks++;
	war->nbr_live = 0;
}

void ft_loop(void)
{
	t_visu		*visu;
	t_corewar	*war;
	t_process	*p;

	war = get_corewar(0);
	visu = get_visu(0);
	while (war->cycle_to_die > 0 && war->nbr_process > 0)
	{
		p = war->all_process;
		board(war, visu);
		if (visu->close)
			break ;
		while (p != NULL)
		{
			if (!p->cycle_create || p->cycle_create < war->cycle)
				ft_exec(p, war);
			p = p->next;
		}
		if ((war->cycle == (war->cycle_last_check + war->cycle_to_die)) || war->cycle_to_die < 1)
		{
			war->cycle_last_check = war->cycle;
			ft_Controlle(war);
		}
		war->cycle++;
	}
	print_winner(war, visu);
}