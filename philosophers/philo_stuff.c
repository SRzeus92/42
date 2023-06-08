/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgolino <fgolino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 10:58:21 by fgolino           #+#    #+#             */
/*   Updated: 2023/06/08 08:27:51 by fgolino          ###   ########.fr       */
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
	if (full_or_dead(philo))
		unlocker(philo, 3);
	else if (!full_or_dead(philo)
		&& philo->right_fork != 0)
	{
		philo->action = EATING;
		print_action(philo->info, philo);
		philo->last_meal = get_time(philo->info);
		ft_sleep((philo->info->time_eat), philo);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo->eat_num++;
	}
	if (!full_or_dead(philo)
		&& philo->right_fork != 0)
	{
		philo->action = SLEEPING;
		print_action(philo->info, philo);
		ft_sleep((philo->info->sleep_time), philo);
	}
	philo->action = THINKING;
	if (!full_or_dead(philo))
		print_action(philo->info, philo);
}

void	lock_forks(t_philo	*philo)
{
	ft_sleep(philo->philo_id, philo);
	if (!full_or_dead(philo))
		pthread_mutex_lock(philo->left_fork);
	philo->action = PICKING_FORK;
	if (!full_or_dead(philo))
		print_action(philo->info, philo);
	if (full_or_dead(philo))
		return (unlocker(philo, 1));
	if (philo->right_fork == 0)
	{
		ft_sleep(philo->info->time_death, philo);
		return ;
	}
	if (!full_or_dead(philo))
		pthread_mutex_lock(philo->right_fork);
	if (!full_or_dead(philo))
		print_action(philo->info, philo);
	if (full_or_dead(philo))
		return (unlocker(philo, 3));
}

void	*philo_routine(void *plato)
{
	t_philo	*philo;

	philo = (t_philo *)plato;
	while (1)
	{
		if (philo->info->philo_dead == 1 && philo->is_dead == 0)
			return (0);
		else if (philo->is_dead == 1 && philo->info->philo_dead == 0)
			return (philo_death(philo));
		if (all_full(philo->info))
			return (0);
		if ((get_time(philo->info) - philo->last_meal)
			>= philo->info->time_death)
		{
			philo->is_dead = 1;
			continue ;
		}
		if (!(philo->info->philo_dead == 1) && philo->is_dead == 0)
			lock_forks(philo);
		if (!full_or_dead(philo)
			&& philo->right_fork != 0)
			philo_eater(philo);
		if (philo->info->philo_dead && philo->is_dead)
			return (0);
	}
}
