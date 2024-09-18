/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:28:31 by luiberna          #+#    #+#             */
/*   Updated: 2024/09/17 23:20:21 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_dinner(t_info *info, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_destroy(&(info->fork[i]));
		i++;
	}
	pthread_mutex_destroy(&(info->write));
	pthread_mutex_destroy(&(info->died_mutex));
	pthread_mutex_destroy(&(info->meal_mutex));
}

void	eating_dinner(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&(info->fork[philo->left_fork]));
		mutex_write(info, philo->id, "has taken a fork");
		pthread_mutex_lock(&(info->fork[philo->right_fork]));
	}
	else
	{
		pthread_mutex_lock(&(info->fork[philo->right_fork]));
		mutex_write(info, philo->id, "has taken a fork");
		pthread_mutex_lock(&(info->fork[philo->left_fork]));
	}
	mutex_write(info, philo->id, "has taken a fork");
	pthread_mutex_lock(&(info->meal_mutex));
	mutex_write(info, philo->id, "is eating");
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(info->meal_mutex));
	get_to_sleep(info, info->time_to_eat);
	pthread_mutex_lock(&(info->meal_mutex));
	philo->times_ate++;
	pthread_mutex_unlock(&(info->meal_mutex));
	pthread_mutex_unlock(&(info->fork[philo->right_fork]));
	pthread_mutex_unlock(&(info->fork[philo->left_fork]));
}

void	*dinner_routine(void *void_philo)
{
	int		i;
	t_philo	*philo;
	t_info	*info;

	i = 0;
	philo = (t_philo *)void_philo;
	info = philo->info;
	if (philo->id % 2)
		usleep(20000);
	while (1)
	{
		pthread_mutex_lock(&(info->died_mutex));
		if (info->died)
		{
			pthread_mutex_unlock(&(info->died_mutex));
			break;
		}
		pthread_mutex_unlock(&(info->died_mutex));
		eating_dinner(philo);
		pthread_mutex_lock(&(info->meal_mutex));
		if (info->all_ate)
		{
			pthread_mutex_unlock(&(info->meal_mutex));
			break ;
		}
		pthread_mutex_unlock(&(info->meal_mutex));
		mutex_write(info, philo->id, "is sleeping");
		get_to_sleep(info, info->time_to_sleep);
		mutex_write(info, philo->id, "is thinking");
		i++;
	}
	return (NULL);
}

void	start_dinner(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	while (i < info->nb_philo)
	{
		pthread_create(&(info->philo[i].thread_id), NULL, dinner_routine,
			&(info->philo[i]));
		pthread_mutex_lock(&(info->meal_mutex));
		info->philo[i].last_meal = get_time();
		pthread_mutex_unlock(&(info->meal_mutex));
		i++;
	}
	check_death(info, info->philo);
	end_dinner(info, info->philo);
}
