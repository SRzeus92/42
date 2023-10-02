/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 15:38:35 by fgolino           #+#    #+#             */
/*   Updated: 2023/10/02 17:33:36 by fgolino          ###   ########.fr       */
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

char	**pipe_finder(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (info->instr_token && info->instr_token[i])
	{
		j = 0;
		while (info->instr_token[i][j])
		{
			
		}
	}
}

void	free_stuff(t_info *info, int flag)
{
	if (flag == 1)
	{
		free(info->instruction);
		free_matrix(info->instr_token);
		info->instr_len = 0;
		info->num_arg = 0;
		info->instr_token = NULL;
	}
	else
	{
		free(info->current_path);
		free(info->user);
		free_matrix(info->global_path);
		free_matrix(info->instr_token);
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
			if (i + 1 == info->instr_len)
			{
				printf("Syntax error\n");
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
