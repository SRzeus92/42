/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:06:49 by fgolino           #+#    #+#             */
/*   Updated: 2023/10/19 11:35:12 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

int	check_redirection(char *str, t_info *info)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			while (str[i] != c)
				i++;
		}
		if (str[i] == '>')
			output_router(info, str, i);
		else if (str[i] == '<')
			input_router(info, str, i);
		if (info->is_error == 1)
			return (1);
		i++;
	}
	return (0);
}

int	redirector(t_info *info)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (info->instr_token[i])
	{
		if (check_redirection(info->instr_token[i], info))
		{
			info->exit_status = 2;
			// qui aggiungi i vari tipi di exit_status a seconda del tipo di errore || 1 per permission deniend ecc...
			return (1);
		}
	}	
	return (0);
}

void	output_router(t_info *info, char *str, int col)
{
	//if (info->instr_token[row][col + 1] == '>')
	// qui fai open in append mode
	
}	

void	input_router(t_info *info, char *str, int col)
{
	int		i;
	char	c;

	i = col + 1;
	c = 0;
	if (str[i] == '<')
		return ; // input_delim()
	if (str[i] != 0)
	{
		while (str[i])
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				c = str[i];
				while (str[i] != c)
					i++;
			}
			if (str[i] == ">" || str[i] == "<")
				break ;
			i++;
		}
		if (c == '"' || c == '\'')
			quote_remover(str, c, i - 2);
		fd_input(info, str);
	}
}

void fd_input(t_info *info, char *str)
{
	// devi prendere tutto ciò che sta dopo il ">" fare una stringa e usarla come path per il file dove dobbiamo scrivere
	return ;
}
