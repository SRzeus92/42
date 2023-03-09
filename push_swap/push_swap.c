/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:47:50 by fgolino           #+#    #+#             */
/*   Updated: 2023/03/09 12:35:50 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_inserter(char	**params, long **stack, int i)
{
	int	j;
	int	z;
	int	len;

	j = 0;
	z = 0;
	while (j++ < i)
		stack[0][j - 1] = ft_atoi(params[j - 1 + 1]);
	len = --j;
	while (j > 0)
	{
		z = j - 2;
		while (z >= 0)
		{
			if ((stack[0][j - 1] == stack[0][z--]) ||
			stack[0][j - 1] > 2147483647 || stack[0][j - 1] < -2147483648)
			{
				ft_printf("Error\n");
				return (-1);
			}
		}
		j--;
	}
	return (len);
}

int	check_parameters(char **params, int num)
{
	int	i;

	while (num > 1)
	{
		i = 0;
		while (params[num - 1][i])
		{
			if (params[num - 1][i] < 48 || params[num - 1][i] > 57)
			{
				ft_printf("Error\n");
				return (-1);
			}
			i++;
		}
		num -= 1;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	long	*stack_a;
	long	*stack_b;
	int		len_a;
	int		len_b;

	if (argc < 2)
		return (0);
	if (check_parameters(argv, argc) != 0)
		return (0);
	stack_a = (long *)malloc(sizeof(long) * (argc - 1));
	stack_b = (long *)malloc(sizeof(long) * (argc - 1));
	if (stack_a == 0)
	{
		free(stack_a);
		return (0);
	}
	len_a = stack_inserter(argv, &stack_a, (argc - 1));
	len_b = 0;
	if (len_a <= 0)
		return (0);
}