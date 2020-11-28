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

void									ft_exec(t_process *p, t_corewar *war)
{
	static	int							(*func[])(t_process *) = {ft_live,
	ft_ld, ft_st,
	ft_add, ft_sub, ft_and, ft_or, ft_xor, ft_zjmp, ft_ldi,
	ft_sti, ft_fork, ft_lld, ft_lldi, ft_lfork, ft_aff};
	int									i;

	p->pc %= MEM_SIZE;
	i = hex(addr_to_hex(&war->arena[p->pc], 1));
	if (i >= 1 && i <= 16)
	{
		if ((p->cycle_count) == (g_op_tab[i - 1].nbr_cycler - 1))
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

static	void							task_die_cursor(
t_process **list_process, t_process *tmp, t_process **head)
{
	t_corewar							*war;

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

t_process								*die_cursor(t_corewar *war,
t_process *list_process)
{
	t_process							*head;
	t_process							*tmp;

	head = list_process;
	tmp = NULL;
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
	return (head);
}

static	void							ft_controlle(t_corewar *war)
{
	int									i;

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
		if (visu && visu->close)
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
			ft_controlle(war);
		}
		war->cycle++;
	}
	print_winner(war, visu);
}

// void									ft_loop(void)
// {
// 	t_corewar							*war;
// 	t_process							*p;

// 	war = get_corewar(0);
// 	while (war->cycle_to_die > 0 && war->nbr_process > 0)
// 	{
// 		p = war->all_process;
// 		while (p != NULL)
// 		{
// 			if (!p->cycle_create || p->cycle_create < war->cycle)
// 				ft_exec(p, war);
// 			p = p->next;
// 		}
// 		if ((war->cycle == (war->cycle_last_check + war->cycle_to_die)) ||
// 			war->cycle_to_die < 1)
// 		{
// 			war->cycle_last_check = war->cycle;
// 			ft_controlle(war);
// 		}
// 		war->cycle++;
// 	}
// 	ft_print_arena();
// }
