/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:39:20 by zdasser@stu       #+#    #+#             */
/*   Updated: 2022/05/09 11:55:40 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				left;
	int				right;
	long			last_time_ate;
	pthread_mutex_t	check_mutex;
	pthread_t		thread;
	int				n_times_ate;
	int				num;
	int				n;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				n_toeat;
	int				end;
	int				dead;
	int				num_of_eat_finish_philo;
}	t_philo;

typedef struct s_data
{
	int				number;
	int				number_philo_finished;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	int				philo_dead;
	long long		start_time;
	int				n_thread;
	pthread_t		monitor;
	int				n_of_time_to_eat;
	t_philo			*philo;
}	t_data;

void		*actions(void *arg);
void		*monitor(void *argv);
void		*monitor_each_must_eat(void *argv);
long long	time_to_ms(struct timeval now);
void		*philo(void *args);
void		*monitor(void *args);
void		philo_eat(t_data *main, int i);
void		philo_sleep(t_data *main, int i);
void		philo_think(t_data *main, int i);
int			philo_is_dead(t_data *main, int *i);
void		drop_forks(t_data *main, int i);
long long	ft_time(void);
int			ft_print(t_data *main, int id, char *status);
long long	t_time(long long time);
void		ft_sleep(int j);
int			ft_atoi(char *str);
int			join_threads(t_data *data);
int			destroy_threads(t_data *data);
void		unlock_forks(t_data *data);
#endif