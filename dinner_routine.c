/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:29:45 by luiberna          #+#    #+#             */
/*   Updated: 2024/09/20 19:30:40 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_died(t_info *info)
{
	pthread_mutex_lock(&(info->died_mutex));
	if (info->died)
		return (pthread_mutex_unlock(&(info->died_mutex)), 1);
	pthread_mutex_unlock(&(info->died_mutex));
	return (0);
}

int	check_all_ate(t_info *info)
{
	pthread_mutex_lock(&(info->meal_mutex));
	if (info->all_ate)
		return (pthread_mutex_unlock(&(info->meal_mutex)), 1);
	pthread_mutex_unlock(&(info->meal_mutex));
	return (0);
}

void	routine_sleep_and_think(t_philo *philo, t_info *info)
{
	mutex_write(info, philo->id, "is sleeping");
	get_to_sleep(info, info->time_to_sleep);
	mutex_write(info, philo->id, "is thinking");
}

int	handle_single_philo(t_philo *philo, t_info *info)
{
	if (info->nb_philo == 1)
	{
		pthread_mutex_lock(&(info->fork[philo->left_fork]));
		mutex_write(info, philo->id, "has taken a fork");
		get_to_sleep(info, info->time_to_die);
		mutex_write(info, philo->id, "died");
		pthread_mutex_unlock(&(info->fork[philo->left_fork]));
		pthread_mutex_lock(&(info->died_mutex));
		info->died = 1;
		pthread_mutex_unlock(&(info->died_mutex));
		return (1);
	}
	return (0);
}

void	*dinner_routine(void *void_philo)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)void_philo;
	info = philo->info;
	if (handle_single_philo(philo, info))
		return (NULL);
	if (philo->id % 2)
		usleep(20000);
	while (1)
	{
		if (check_died(info))
			break ;
		eating_dinner(philo);
		if (check_all_ate(info))
			break ;
		routine_sleep_and_think(philo, info);
	}
	return (NULL);
}
