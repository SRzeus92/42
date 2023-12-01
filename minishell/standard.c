/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   standard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:58:20 by fgolino           #+#    #+#             */
/*   Updated: 2023/12/01 16:43:51 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_stdin(t_info *info)
{
	if (info->pipe_fd1[0] && !info->pipe_fd1[1])
	{
		close(info->pipe_fd1[0]);
		dup2(info->temp_stdin, STDIN_FILENO);
		info->pipe_fd1[0] = 0;
		info->temp_stdin = 0;
	}
	else if (info->pipe_fd2[0] && !info->pipe_fd2[1])
	{
		close(info->pipe_fd2[0]);
		dup2(info->temp_stdin, STDIN_FILENO);
		info->pipe_fd2[0] = 0;
		info->temp_stdin = 0;
	}
	if (info->temp_stdin)
	{
		if (info->temp_in_fd)
			close(info->temp_in_fd);
		dup2(info->temp_stdin, STDIN_FILENO);
		info->temp_in_fd = 0;
		info->temp_stdin = 0;
	}
}

void	reset_stdout(t_info *info)
{
	info->pos_pipe = 0;
	if (info->tmp_fd)
	{
		tmp_file_creator(info, 2, 0);
		tmp_file_creator(info, 3, 0);
	}
	if (info->temp_stdout)
	{
		if (info->temp_out_fd)
			close(info->temp_out_fd);
		dup2(info->temp_stdout, STDOUT_FILENO);
		info->temp_stdout = 0;
		info->temp_out_fd = 0;
	}
}

void	reset_all(t_info *info)
{
	reset_stdin(info);
	if (info->pipe_fd1[1])
	{
		close(info->pipe_fd1[1]);
		dup2(info->temp_stdout, STDOUT_FILENO);
		info->pipe_fd1[1] = 0;
		info->temp_stdout = 0;
		if (!info->temp_stdin)
			info->temp_stdin = dup(STDIN_FILENO);
		dup2(info->pipe_fd1[0], STDIN_FILENO);
	}
	else if (info->pipe_fd2[1])
	{
		close(info->pipe_fd2[1]);
		dup2(info->temp_stdout, STDOUT_FILENO);
		info->pipe_fd2[1] = 0;
		info->temp_stdout = 0;
		if (!info->temp_stdin)
			info->temp_stdin = dup(STDIN_FILENO);
		dup2(info->pipe_fd2[0], STDIN_FILENO);
	}
	reset_stdout(info);
}
