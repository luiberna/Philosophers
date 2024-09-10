/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:40:41 by luiberna          #+#    #+#             */
/*   Updated: 2024/09/09 20:49:08 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		mutex_write(t_info *info, int philo_id, char *action)
{
	pthread_mutex_lock(&(info->write));
	if (!(info->died))
		printf("%lli %i %s\n", get_time() - info->start_time, philo_id + 1, action);
	pthread_mutex_unlock(&(info->write));
	return ;
}

void	get_to_sleep(t_info *info, long long time)
{
	long long now;

	now = get_time();
	while(!(info->died))
	{
		if (get_time() - now >= time)
			break;
		usleep(100);
	}
}

long long	get_time(void)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	return((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int     	ft_strdigit(char *str)
{
    int     i;

    i = 0;
	while (str[i])
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

int     ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	nb;

	nb = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			s = -s;
			i++;
		}
		else
			i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (s * nb);
}
