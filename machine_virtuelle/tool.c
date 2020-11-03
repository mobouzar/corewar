#include "../include/corewar.h"
// #include "../include/op_tab2.h"

t_op op_tab2[17] =
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
		{0, 0, {0}, 0, 0, 0, 0, 0}};

/*
** new func for get size of beyt flag :
*/
int get_size_arg(unsigned char flg, int nb_arg, int opcode)
{
	if ((flg & IND_CODE) == IND_CODE)
	{
		// printf("indff= %d\n\n",flg);
		if ((op_tab2[opcode - 1].args[nb_arg] ^ IND_CODE) != IND_CODE)
			G_error = true;
		return 2;
	}
	else if ((flg & REG_CODE) == REG_CODE)
	{
		// printf("regff= %d\n\n",flg);
		if ((op_tab2[opcode - 1].args[nb_arg] ^ REG_CODE) != REG_CODE)
			G_error = true;
		return 1;
	}

	else if ((flg & DIR_CODE) == DIR_CODE)
	{
		if ((op_tab2[opcode - 1].args[nb_arg] ^ DIR_CODE) != DIR_CODE)
			G_error = true;
		if (!op_tab2[opcode - 1].size_dir)
			return 4;
		return 2;
	}
	return 0;
}

int get_size_beyt_flag(unsigned char flg, int opcode)
{
	int i;
	// int j;
	int count;

	i = -1;
	count = 0;
	// printf("un = %u\n\n", flg);
	while (++i < op_tab2[opcode - 1].nbr_args)
	{
		count += get_size_arg(((flg >> (6 - (i * 2))) & 0x3), i, opcode);
	}
	return count;
}

/*
**
*/

int overrided_pos(int size, int cursor0)
{
	// if (pos >= 0)
	// 	return (pos % IDX_MOD);
	// else
	// {
	// 	if (pos < IDX_MOD)
	// 		return (MEM_SIZE + pos);
	// 	else
	// 		return (MEM_SIZE - (pos % IDX_MOD));
	// }
	// return (0);


	if (size >= 0)
	{
		size = cursor0 + (size % IDX_MOD);
		size = size % MEM_SIZE;
	}
	else
	{
		// printf("((-1 * size) IDX_MOD) =  %d\n\n", ((-1 * size) % IDX_MOD));
		// printf("(cursor0 + (((-1 * size)  IDX_MOD) * -1)) == %d \n\n",(cursor0 + (((-1 * size) % IDX_MOD) * -1)));
		return MEM_SIZE + (cursor0 + (((-1 * size) % IDX_MOD) * -1));
	}
	return (size);
}

void cpy_reg_to_arena(t_process *p, int cursor0, int size, int reg)
{
	t_corewar *war;

	war = get_struct(NULL);
	// printf("\nmodoll = %d\n\n\n", overrided_pos( size));//
	size = overrided_pos(size , cursor0);
	// printf("over= %d   \n\n", size);
	// size = cursor0 + (size % IDX_MOD);
	// size = size % MEM_SIZE;
	// printf("size  = =  %d     reg = %d   \n\n\n", size, reg);
	if (size + 4 > MEM_SIZE)
	{
		ft_memcpy((void *)&war->arena[size], (void *)&p->regster[reg - 1], (MEM_SIZE - size));
		ft_memcpy((void *)&war->arena[0], (void *)&p->regster[reg - 1], 4 - (MEM_SIZE - size));
	}
	else
		ft_memcpy((void *)&war->arena[size], (void *)&p->regster[reg - 1], 4);
}

int read_regster(t_process *proc)
{
	t_corewar *war;
	unsigned char i;

	i = 0;
	war = get_struct(NULL);
	ft_memcpy((void *)&i, (void *)&war->arena[proc->pc], 1);
	i = hex(addr_to_hex(&i, 1));
	if (i >= 0 && i <= 16)
		return (i);
	G_error = true;
	return (-1);
}

void cpy_arena_to_reg(t_process *p, int cursor0, int size, int reg)
{

	t_corewar *war;

	war = get_struct(NULL);
	// size = overrided_pos(cursor0 + size);
	// size = cursor0 + (size % IDX_MOD);
	// size = size % MEM_SIZE;
	size = overrided_pos(size , cursor0);
	// printf("\n sssss= %d \n\n", size);
	if (size + 4 > MEM_SIZE)
	{
		ft_memcpy((void *)&p->regster[reg - 1], (void *)&war->arena[size], (MEM_SIZE - size));
		ft_memcpy((void *)&p->regster[reg - 1] + (MEM_SIZE - size), (void *)&war->arena[0], 4 - (MEM_SIZE - size));
	}
	else
	{
		ft_memcpy((void *)&p->regster[reg - 1], (void *)&war->arena[size], 4);
	}
}

/*
** new func ldi_cpy;
*/
unsigned int cpy_arena_to_var(t_process *p, int size, int cursor0, int opcode)
{
	unsigned int stock = 0;
	t_corewar *war;

	(void)p;
	(void)opcode;
	war = get_struct(0);
	if (opcode == 13)/////postv negative
		size = cursor0 + size;
	else
		size = overrided_pos(size , cursor0);
		// size = cursor0 + (size % IDX_MOD);
	size = size % MEM_SIZE;
	if ((size + 4) >= MEM_SIZE)
	{
		ft_memcpy((void *)&stock, (void *)&war->arena[size], (MEM_SIZE - size));
		ft_memcpy((void *)&stock + (MEM_SIZE - size), (void *)&war->arena[0], 4 - (MEM_SIZE - size));
	}
	else
		ft_memcpy((void *)&stock, (void *)&war->arena[size], 4);
	return (stock);
}

unsigned int return_data_of_arg(t_process *proc, unsigned char flg, int opcode, int cursor0)
{
	t_corewar *war;
	unsigned int st;
	war = get_struct(NULL);
	st = 0;
	if ((flg & IND_CODE) == IND_CODE)
	{
		ft_memcpy((void *)&st, (void *)&war->arena[proc->pc], 2);
		// printf("\n\nsing = %d\n\n", ft_sign(st, 2));

		st = cpy_arena_to_var(proc, (ft_sign(st, 2)), cursor0, opcode);
		printf("hex = %s\n\n", addr_to_hex(&st, 4));

		proc->pc += 2;
		return (st);
	}
	else if ((flg & REG_CODE) == REG_CODE)
	{
		st = read_regster(proc);
		proc->pc++;
		return (proc->regster[st - 1]);
	}
	else if ((flg & DIR_CODE) == DIR_CODE)
	{
		if (!op_tab2[opcode - 1].size_dir)
		{
			ft_memcpy((void *)&st, (void *)&war->arena[proc->pc], 4);
			printf("hex = %s\n\n", addr_to_hex(&st, 4));
			proc->pc += 4;
			return (st);
		}
		ft_memcpy((void *)&st, (void *)&war->arena[proc->pc], 2);
		proc->pc += 2;
		return (st);
	}
	return 0;
}
