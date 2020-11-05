#include "../include/corewar.h"

int hextodecimal(char val)
{
	const char tab[16] = "0123456789abcdef";
	int i;
	i = -1;
	while (++i < 16)
	{
		if (val == tab[i])
		{
			return (i);
		}
	}
	return (-1);
}
int hex(char *value)
{
	int result;
	int base;
	int len;

	base = 1;
	result = 0;
	len = ft_strlen(value);
	while (--len >= 0)
	{
		result += hextodecimal(value[len]) * base;
		base *= 16;
	}
	return (result);
}

char *addr_to_hex(void *addr, size_t size)
{
	const char *str = "0123456789abcdef";
	char_t *p;
	int j;
	int i;
	char *s;

	s = ft_strnew(size * 2);
	p = (char_t *)addr;
	i = -1;
	j = 0;
	j = size - 1;
	i = (int)(size * 2);
	ft_memset((void *)s, 0, sizeof(s));
	while (i >= 0 && j >= 0)
	{
		s[--i] = str[p[j] % 16];
		s[--i] = str[(p[j] / 16) % 16];
		j--;
	}
	// printf("%s ",s);
	return (s);
}
static short rev_4(unsigned char *s)
{
	unsigned short a;

	a = 0;
	//  printf("sss => %d\n", *(int*)s);
	a |= ((s[0]) & (0xff)) << 24;
	a |= ((s[1]) & (0xff)) << 16;
	a |= ((s[2]) & (0xff)) << 8;
	a |= ((s[3]) & (0xff));
	a = (a - 1);
	a = ~a;
	return (a * -1);
}
static short rev_2(unsigned char *s)
{
	unsigned short a;

	a = 0;
	//  printf("sss => %d\n", *(int*)s);

	a |= ((s[0]) & (0xff)) << 8;
	a |= ((s[1]) & (0xff));
	a = (a - 1);
	a = ~a;
	return (a * -1);
}

int ft_sign(unsigned int s, int size)
{
	char *str = addr_to_hex(&s, size);
	// printf("s => %s\n", str);
	printf("\n\n\n  sstr   => %s\n\n\n", str);
	if (str[0] >= '0' && str[0] <= '7')
		return (hex(str));
	else
	{
		return (size == 4 ? rev_4((unsigned char *)&s) : rev_2((unsigned char *)&s));
	}
	return 0;
}

unsigned int binary_rev(unsigned int s)
{
	unsigned int a;

	a = 0;
	a |= ((s) & (0xff)) << 24;
	a |= ((8 >> s) & (0xff)) << 16;
	a |= ((16 >> s) & (0xff)) << 8;
	a |= ((24 >> s) & (0xff));
	return (a);
}

// int main(int argc, char **argv)
// {
// 	printf("resit  = %d\n\n", hex(argv[1]));

// }
// int _hex_to_int_(int value)
// {

// }
// 		// value |= (( str >> 0) & (0xff)) <<24;
// 		// value |= (( str >> 8) & (0xff)) <<16;
// 		// value |= (( str >> 16) & (0xff)) <<8;
// 		// value |= (( str >> 24) & (0xff)) <<0;

unsigned int _int_(void *adress, int lenght)
{
	int value;
	int i;
	unsigned int str;

	value = 0;
	i = -1;
	str = 0;
	str = (unsigned int)adress;
	while (++i < lenght)
		value |= ((str >> (i * 8)) & (0xff)) << ((lenght * 4) - i * 8);
	return (value);
}