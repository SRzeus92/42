/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:58:21 by fgolino           #+#    #+#             */
/*   Updated: 2023/06/06 18:32:25 by fgolino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_generator(t_info *info)
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
		info->philosophers[i].left_fork = &(info->forks[i]);
		if (info->num_philo > 1)
			info->philosophers[i].right_fork = &(info->forks[(i + 1)
					% info->num_philo]);
		else
			info->philosophers[i].right_fork = 0;
		i++;
	}
}

void	start_philo_thread(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_philo)
	{
		pthread_create(&(info->philosophers[i].thread_id), NULL, &philo_routine,
			(void *)&(info->philosophers[i]));
		i++;
	}
	i = 0;
	while (i < info->num_philo)
		pthread_join((info->philosophers[i++].thread_id), NULL);
}

void	philo_eater(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->write_right);
	if (philo->info->philo_dead == 0 && is_dead(philo) == 0
		&& philo->right_fork != 0)
	{
		philo->action = EATING;
		print_action(philo->info, philo);
		philo->last_meal = get_time(philo->info);
		pthread_mutex_unlock(&philo->info->write_right);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		usleep((philo->info->time_eat) * 1000);
	}
	if (philo->info->philo_dead == 0 && is_dead(philo) == 0
		&& philo->right_fork != 0)
	{
		philo->action = SLEEPING;
		print_action(philo->info, philo);
		usleep((philo->info->sleep_time) * 1000);
	}
}

void	lock_forks(t_philo	*philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->info->write_right);
	philo->action = PICKING_FORK;
	if (philo->info->philo_dead == 0 && is_dead(philo) == 0)
		print_action(philo->info, philo);
	else
	{
		pthread_mutex_unlock(&philo->info->write_right);
		return ;
	}
	pthread_mutex_unlock(&philo->info->write_right);
	if (philo->right_fork == 0)
		usleep(philo->info->time_death * 1000);
	else
		pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->info->write_right);
	if (philo->info->philo_dead == 0 && is_dead(philo) == 0)
		print_action(philo->info, philo);
	else
	{
		pthread_mutex_unlock(&philo->info->write_right);
		return ;
	}
	pthread_mutex_unlock(&philo->info->write_right);
}

void	*philo_routine(void *plato)
{
	t_philo	*philo;

	philo = (t_philo *)plato;
	while (1)
	{
		if (philo->info->philo_dead == 1 && philo->is_dead == 0)
			return (0);
		else if (philo->is_dead == 1)
			return (philo_death(philo));
		if ((get_time(philo->info) - philo->last_meal)
			>= philo->info->time_death)
		{
			philo->is_dead = 1;
			philo->info->philo_dead = 1;
			continue ;
		}
		if (!(philo->info->philo_dead == 1) && philo->is_dead == 0)
			lock_forks(philo);
		if (philo->info->philo_dead == 0 && is_dead(philo) == 0
			&& philo->right_fork != 0)
			philo_eater(philo);
	}
}
