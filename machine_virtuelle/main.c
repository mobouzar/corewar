/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 18:06:05 by yelazrak          #+#    #+#             */
/*   Updated: 2020/03/13 18:26:19 by yelazrak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** in this file main programe principall
**
**
**
**
**
**
**
**
*/

#include "../include/corewar.h"

int get_id_player(int id, int flg)
{
	static int array[] = {0, 0, 0, 0};
	int i;
	// static int Counter_id;

	i = -1;
	if(flg)
	{
		if (id != -1)
		{
			if (array[id - 1] == 2) //222ya3ni mokhd
			{
				array[id - 1] = 1;
				return id;
			}
			else
				return -1;
		}
		while (++i < 4)
		{
			if (!array[i])
			{
				array[i] = 1;
				return i + 1;
			}
		}
	}
	else
	{
		array[id] = 2;
	}
	// i = -1;

	// while(++i< 4)
	// {
	// 	printf("\n\nflg = %d  i== %d   get_id  = %d\n\n\n", flg,i,  array[i]);
	// }

	return -1;
}
int is_intger(char *arg)
{
	int i;
	int n;
	if (!arg)
		return (0);
	i = -1;
	n = ft_strlen(arg);
	while (++i < n)
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return 1;
}

int get_id(char **argv)
{


	int i;
	int index;

	i = 0;
	index = 1;
	
	while (argv[i])
		{
			if (!ft_strcmp(argv[i], "-n"))
			{
				if (!argv[i + 1] || !is_intger(argv[i + 1]))
					return 0;
				index = ft_atoi(argv[i + 1]);
				if (!(index > 0 && index < 5))
					return 0;
				get_id_player(index -1 , 0);
			}
			i++;
		}

	return -1;
}

static int manage_file(t_corewar *war, int id, char *file_name)
{
	t_header *lst;
	int n;

	n = ft_strlen(file_name);
	//printf("namefile  = %s        id = %d\n\n", file_name, 0);
	if ((id = get_id_player(id,1)) < 0 || !file_name)
		return 0;
	// if (n < 6 || ft_strcmp(file_name + (n - 4), ".cor"))
	// 	return 0;
	//ft_putendl("file_mangement_out\n\n");
	if (!(lst = ft_cin_file(file_name)))
		return 0;
	war->players[id - 1].data_file = lst;
	war->nbr_fighters++; ////////////
	return 1;
}

int is_int(t_corewar *war, char *arg)
{
	// int i;
	// int n;
	// (void)war;
	// if (!arg)
	// 	return (0);
	// i = -1;
	// n = ft_strlen(arg);
	// printf("dump  = %s\n", arg);
	// while (++i < n)
	// {
	// 	if (!ft_isdigit(arg[i]))
	// 		return (0);
	// }
	if(!is_intger(arg))
		return 0;
	war->dump = ft_atoi(arg);
	//printf("war->dump  = %d\n", war->dump);

	return 1;
}

void Adaptation_player(t_corewar *war)
{
	int i;
	int j;

	i = -1;
	while (++i < 3)
	{
		if (!war->players[i].data_file)
		{
			j = i;
			while (++j < 4)
			{
				if (war->players[j].data_file)
				{
					war->players[i].data_file = war->players[j].data_file;
					war->players[j].data_file = NULL;
				}
			}
		}
	}
}

void ft_copy_player_arena(t_corewar *war)
{
	t_header *lst;
	int i;
	int position;
	int pa;

	i = -1;
	pa = 4096 / war->nbr_fighters;
	position = 0;
	//Adaptation_player(war);
	while (++i < war->nbr_fighters)
	{
		lst = war->players[i].data_file;
		printf("name player = %s   id_player  %d   \n\n", lst->prog_name, i);
		ft_memcpy(&war->arena[position], lst->champ, hex(addr_to_hex(&lst->prog_size, 4)));
		war->players[i].Starting_point = position;
		position += pa;
	}
}

int Parsing(t_corewar *war, int argc, char **argv)
{
	int i = 0;
	int index = -1;

	if (argc < 2)
		return (0);
	while (++i < argc)
	{
		printf("\n\ni = %d \n\n", i);
		if (!ft_strcmp(argv[i], "-dump"))
		{
			if (!is_int(war, argv[i + 1]))
			{
				printf("err -dump \n\n");
				return (0);
			}
			i++;
		}
		else if (!ft_strcmp(argv[i], "-n"))
		{
			if (!argv[i + 1])
				return 0;
			index = ft_atoi(argv[i + 1]);
			if (!(index > 0 && index < 5) || !manage_file(war, index, argv[i + 2]))
			{
				printf("err -n \n\n");
				return 0;
			}
			i += 2;
			continue;
		}
		else
		{
			if (!manage_file(war, -1, argv[i]))
			{
				printf("err file \n\n");

				return 0;
			}
		}
	}
	printf("copy_file arena\n\n");
	ft_copy_player_arena(war);
	return 1;
}

void Free_Process(t_process *p)
{
	if (p->next)
		Free_Process(p->next);
	ft_memdel((void **)&p);
}

void Free_Corewar(t_corewar *war)
{
	int i;

	i = -1;
	ft_memdel((void **)&war->arena);
	while (++i < war->nbr_fighters)
	{
		ft_memdel((void **)&war->players[i].data_file);
		Free_Process(war->players[i].process);
	}
	ft_memdel((void **)&war);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_corewar *war;

	if (!(war = (t_corewar *)malloc(sizeof(t_corewar))))
		return (1);
	ft_memset((void *)war, 0, sizeof(t_corewar));
	war->arena = ft_get_arena();
	get_id(argv); ///
	Parsing(war, argc, argv);
	ft_init_process(war);
	get_struct(war);
	 ft_loop();
	//ft_print_arena();
	// Free_Corewar(war);
	return (0);
}