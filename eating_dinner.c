/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating_dinner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:26:49 by luiberna          #+#    #+#             */
/*   Updated: 2024/09/24 17:25:37 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	putdown_forks(t_philo *philo, t_info *info)
{
	pthread_mutex_unlock(&(info->fork[philo->right_fork]));
	pthread_mutex_unlock(&(info->fork[philo->left_fork]));
}

void	update_meal_count(t_philo *philo, t_info *info)
{
	pthread_mutex_lock(&(info->meal_mutex));
	philo->times_ate++;
	check_full_belly(info, philo);
	pthread_mutex_unlock(&(info->meal_mutex));

}

void	pickup_forks(t_philo *philo, t_info *info)
{
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
}

void	eating_dinner(t_philo *philo)
{
	t_info	*info;

	info = philo->info;
	pickup_forks(philo, info);
	mutex_write(info, philo->id, "is eating");
	pthread_mutex_lock(&(info->meal_mutex));
	philo->last_meal = get_time();
	pthread_mutex_unlock(&(info->meal_mutex));
	get_to_sleep(info, info->time_to_eat);
	update_meal_count(philo, info);
	putdown_forks(philo, info);
}
