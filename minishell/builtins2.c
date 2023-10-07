/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:49:24 by fgolino           #+#    #+#             */
/*   Updated: 2023/10/08 00:18:34 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

void	unset_handler(t_info *info)
{
	// questa funzione deve modificare e rimuovere le varibiabili scritte in "environment"
}

int	cd_loop(t_info *info)
{
	int		i;
	char	*tmp;

	i = -1;	
	while (info->global_path[++i])
	{
		tmp = triple_join(info->global_path[i], "/", info->instr_token[1]);
		if (!chdir(tmp))
		{
			free(tmp);
			return (0);
		}
		else
		{
			if (errno == EACCES)
			{
				printf("cd : %s : Permission denied\n", tmp);
				free(tmp);
				return (0);
			}	
		}
		free(tmp);
	}
	return (1);
}