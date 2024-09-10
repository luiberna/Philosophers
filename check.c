/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:30:23 by luiberna          #+#    #+#             */
/*   Updated: 2024/09/10 14:30:46 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    check_full_belly(t_info *info, t_philo *philo)
{
    int i;

    i = 0;
    while (info->times_must_eat != -1 && i < info->nb_philo && philo[i].times_ate >= (info->times_must_eat - 1))
			i++;
    if (i == info->nb_philo)
        info->all_ate = 1;
}

void    check_death(t_info *info, t_philo *philo)
{
	int i;
    long long time_since_last_meal;

	while (!(info->all_ate))
	{
		i = 0;
		while (i < info->nb_philo && !(info->died))
		{
			pthread_mutex_lock(&(info->meal));
            time_since_last_meal = get_time() - philo[i].last_meal;
			if (time_since_last_meal > info->time_to_die)
			{
				mutex_write(info, i, "died");
				info->died = 1;
			}
			pthread_mutex_unlock(&(info->meal));
			usleep(100);
            i++;
		}
		if (info->died)
			break ;
		check_full_belly(info, philo);
	}
}
