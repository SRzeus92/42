/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 18:47:49 by fgolino           #+#    #+#             */
/*   Updated: 2023/10/16 12:52:15 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

void	get_environment(t_info *g_info, char **environment)
{
	char	*tmp;

	g_info->environment = matrix_crusher(environment, NULL);
	g_info->global_path = ft_split((getenv("PATH")), ':');
	g_info->user = ft_strdup(getenv("USER"));
	tmp = ft_strjoin(g_info->user, (":~"));
	free(g_info->user);
	g_info->user = tmp;
	signal_rewire();
	g_info->current_path = ft_strdup(getenv("HOME"));
	g_info->temp_stdout = 0;
	chdir(g_info->current_path);
	g_info->instr_token = NULL;
	g_info->current_arg = 0;
	g_info->num_arg = 0;
	g_info->received_signal = 0;
	g_info->exit_status = 0;
}

void	executing(t_info *info)
{
	int	status;

	status = 0;
	start(info);
	if (info->num_arg != 0)
		analizer(info);
	if (info->instr_pid != 0)
	{
		wait(&(status));
		if (WIFEXITED(status))
			info->exit_status = WEXITSTATUS(status);
		signal_rewire();
		if (g_signal == SIGINT)
		{
			printf("\n");
			info->exit_status = 130;
		}
	}
	g_signal = 0;
}

int	main(int argc, char	**argv, char **envp)
{
	t_info	info;

	if (argc > 1)
	{
		printf("Minishell takes no argument\n");
		exit(0);
	}
	get_environment(&info, envp);
	while (1)
	{
		info.instruction = readline(info.user);
		info.instr_pid = 0;
		g_signal = 0;
		if (info.instruction == NULL && info.instr_pid == 0)
			break ;
		executing(&info);
		free_stuff(&info, 1);
	}
	free_stuff(&info, 0);
	return (0);
}
