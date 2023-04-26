#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

void ft_putstr(char *str, int *size)
{
	int i = 0;
	if (!str)
		*size+=write(1, "(null)", 6);
	else
		while (str[i]) 
		{
			*size += write(1, &str[i], 1);
		}
}

void	put_base (long long int num, char *base, int b,int  *size)
{
	if (num < 0)
	{
		*size+=write(1, "-", 1);
		num = -num;
	}
	if (num >= b)
		put_base(num / b, base, b, size);
	*size+=write(1, &base[num % b], 1);
}

int	ft_printf(char *str, ...)
{
	va_list arg;
	int size = 0;

	va_start(arg, str);
	while (*str)
	{
		if (*str == '%' && *(str + 1) == 's')
			ft_putstr(va_arg(arg, char *), &size), str++;
		else if (*str == '%' && *(str + 1) == 'x')
			put_base(va_arg(arg, unsigned int), "0123456789abcdef", 16, &size), str++;
		else if (*str == '%' && *(str + 1) == 'd')
			put_base(va_arg(arg, unsigned int), "0123456789", 10, &size), str++;
		else
			size += write(1, str, 1);
		str++;
	}
	return (va_end(arg), size-=1);
}

int main (void)
{
	int i = 0;
	put_base(ft_printf("robaaaaaa\0 %x\n", 32), "0123456789", 10, &i);
}