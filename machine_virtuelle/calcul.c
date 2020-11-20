#include "../include/corewar.h"

int					hex(char *value)
{
	int				result;
	int				base;
	int				len;

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

char				*addr_to_hex(void *addr, size_t size)
{
	const char		*str = "0123456789abcdef";
	char_t			*p;
	int				j;
	int				i;
	char			*s;

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
	return (s);
}
static	unsigned	int	rev_4(unsigned char *s)
{
	unsigned int	a;

	a = 0;
	a |= ((s[0]) & (0xff)) << 24;
	a |= ((s[1]) & (0xff)) << 16;
	a |= ((s[2]) & (0xff)) << 8;
	a |= ((s[3]) & (0xff));
	a = (a - 1);
	a = ~a;
	return (a * -1);
}
static	short		rev_2(unsigned char *s)
{
	unsigned short	a;

	a = 0;
	a |= ((s[0]) & (0xff)) << 8;
	a |= ((s[1]) & (0xff));
	a = (a - 1);
	a = ~a;
	return (a * -1);
}

int					ft_sign(unsigned int s, int size)
{
	char *str;

	str = addr_to_hex(&s, size);
	if (str[0] >= '0' && str[0] <= '7')
		return (hex(str));
	else
	{
		return (size == 4 ? rev_4((unsigned char *)&s) : rev_2((unsigned char *)&s));
	}
	return 0;
}

