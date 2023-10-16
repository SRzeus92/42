/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:38:35 by fgolino           #+#    #+#             */
/*   Updated: 2023/10/16 12:40:36 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix != NULL && matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	if (matrix != NULL)
	{
		if (matrix[i])
			free(matrix[i]);
		free(matrix);
	}
	return ;
}

void	free_stuff(t_info *info, int flag)
{
	if (flag == 1)
	{
		free(info->instruction);
		free_matrix(info->instr_token);
		info->num_arg = 0;
		info->instr_token = NULL;
	}
	else
	{
		free(info->current_path);
		free(info->user);
		free_matrix(info->global_path);
		free_matrix(info->instr_token);
		free_matrix(info->environment);
		rl_clear_history();
	}
}

int	redirector(t_info *info)
{
	int	i;

	i = 0;
	while (info->instr_token[i] && info->temp_stdout == 0)
	{
		if (ft_strncmp(">", info->instr_token[i], 1) == 0)
		{
			if (i + 1 == info->num_arg)
			{
				printf("syntax error near unexpected token `newline'\n");
				return (-1);
			}
		}
		i++;
	}	
	return (0);
}

char	*triple_join(char *start, char *middle, char *end)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(start, middle);
	tmp2 = ft_strjoin(tmp, end);
	free(tmp);
	return (tmp2);
}

char	*get_global(char **matrix, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (matrix[++i])
	{
		j = 0;
		while (matrix[i][j] != '=')
			j++;
		if (ft_strncmp(matrix[i], str, j) == 0)
		{
			tmp = ft_strdup(&matrix[i][j + 1]);
			return (tmp);
		}
	}
	return (NULL);
}
