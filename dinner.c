/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:28:31 by luiberna          #+#    #+#             */
/*   Updated: 2024/09/20 19:42:02 by luiberna         ###   ########.fr       */
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
