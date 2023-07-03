/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:17:49 by fgolino           #+#    #+#             */
/*   Updated: 2023/07/03 16:48:51 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	philo_generator(t_info_bonus *info)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	info->philosophers = (t_philo *)malloc(sizeof(t_philo) * info->num_philo);
	while (i < info->num_philo)
	{
		info->philosophers[i].philo_id = 1 + i;
		info->philosophers[i].action = 0;
		info->philosophers[i].is_dead = 0;
		info->philosophers[i].eat_num = 0;
		info->philosophers[i].last_meal = 0;
		info->philosophers[i].info = info;
		info->philosophers[i].forks = &(info->forks);
		i++;
	}
}

void	start_processes(t_info *info)
{
	int	i;

	i = -1;
	while (i++ < info->num_philo - 1)
	{
		if (fork())
			continue ;
		bonus_routine(&(info->philosophers[i]));
	}
	while (waitpid(-1, NULL, 0) > 0);
}

void	bonus_routine(t_philo *philo)
{
	while (1)
	{
		if 
	}