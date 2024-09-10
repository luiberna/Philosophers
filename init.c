/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:52:45 by luiberna          #+#    #+#             */
/*   Updated: 2024/09/10 14:20:01 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_input(char **args)
{
	int	nb;

	nb = ft_atoi(args[1]);
	if (nb < 1 || nb > 200 || nb > INT_MAX || !ft_strdigit(args[1]))
		return (1);
	nb = ft_atoi(args[2]);
	if (nb < 1 || nb > INT_MAX || !ft_strdigit(args[2]))
		return (1);
	nb = ft_atoi(args[3]);
	if (nb < 1 || nb > INT_MAX || !ft_strdigit(args[3]))
		return (1);
	nb = ft_atoi(args[4]);
	if (nb < 1 || nb > INT_MAX || !ft_strdigit(args[4]))
		return (1);
	if (args[5])
	{
		nb = ft_atoi(args[5]);
		if (nb < 1 || nb > INT_MAX || !ft_strdigit(args[5]))
			return (1);
	}
	return (0);
}

void	init_philo(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->philo[i].id = i;
		info->philo[i].times_ate = 0;
		info->philo[i].left_fork = i;
		info->philo[i].right_fork = (i + 1) % info->nb_philo;
		info->philo[i].info = info;
		i++;
	}
}

void	init_info(char **args, t_info *info)
{
	int	i;

	info->nb_philo = ft_atoi(args[1]);
	info->time_to_die = ft_atoi(args[2]);
	info->time_to_eat = ft_atoi(args[3]);
	info->time_to_sleep = ft_atoi(args[4]);
	if (args[5])
		info->times_must_eat = ft_atoi(args[5]);
	else
		info->times_must_eat = -1;
	info->died = 0;
	info->all_ate = 0;
	i = 0;
	while (i < info->nb_philo)
	{
		pthread_mutex_init(&(info->fork[i]), NULL);
		i++;
	}
	pthread_mutex_init(&(info->write), NULL);
	pthread_mutex_init(&(info->meal), NULL);
	init_philo(info);
}
