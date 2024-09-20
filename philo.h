/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiberna <luiberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:08:29 by luiberna          #+#    #+#             */
/*   Updated: 2024/09/20 19:55:24 by luiberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

struct	s_info;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				times_ate;
	long long		last_meal;
	pthread_t		thread_id;
	struct s_info	*info;
}					t_philo;

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				all_ate;
	int				died;
	long long		start_time;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	died_mutex;
	pthread_mutex_t	fork[210];
	pthread_mutex_t	write;
	t_philo			philo[210];
}					t_info;

// Check
void				check_full_belly(t_info *info, t_philo *philo);
void				check_death(t_info *info, t_philo *philo);
int					check_philo_death(t_info *info, t_philo *philo, int i);
int					check_all_full(t_info *info, t_philo *philo);

// Eating Dinner
void				eating_dinner(t_philo *philo);
void				pickup_forks(t_philo *philo, t_info *info);
void				putdown_forks(t_philo *philo, t_info *info);
void				update_meal_count(t_philo *philo, t_info *info);

// Dinner Routine
int					check_died(t_info *info);
int					check_all_ate(t_info *info);
void				routine_sleep_and_think(t_philo *philo, t_info *info);
int					handle_single_philo(t_philo *philo, t_info *info);
void				*dinner_routine(void *void_philo);

// Dinner
void				end_dinner(t_info *info, t_philo *philo);
void				eating_dinner(t_philo *philo);
void				*dinner_routine(void *void_philo);
void				start_dinner(t_info *info);

// Init
int					check_input(char **args);
void				init_philo(t_info *info);
void				init_info(char **args, t_info *info);

// Utils
int					ft_strdigit(char *str);
int					ft_atoi(const char *str);
long long			get_time(void);
void				mutex_write(t_info *info, int philo_id, char *action);
void				get_to_sleep(t_info *info, long long time);

#endif