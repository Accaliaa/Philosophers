/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 07:23:03 by zdasser@stu       #+#    #+#             */
/*   Updated: 2022/05/06 20:18:21 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	*philo(void *par)
{
	t_data	*data;
	int		i;

	data = (t_data *)par;
	i = data->n_thread;
	data->thread_state = 1;
	if (data->philo_dead == 0)
	{
		while (data->philo_dead == 0)
		{
			philo_eat(data, i);
			if (data->n_of_time_to_eat == data->philo[i].n_times_ate && \
			data->n_of_time_to_eat)
			{
				data->number_philo_finished++;
			}
			philo_sleep(data, i);
			philo_think(data, i);
		}
	}
	return (NULL);
}

int	check_philo_alive(t_data *data)
{
	int		i;
	long	now;

	i = 0;
	while (data->philo_dead == 0)
	{
		if (data->number_philo_finished == data->number)
			return (0);
		now = ft_time();
		if ((now - data->philo[i].last_time_ate) > data->philo[i].time_die)
		{
			pthread_mutex_lock(&data->write_mutex);
			now = t_time(data->start_time);
			printf("%ld  %d  %s\n", now, data->philo[i].n, "is dead");
			data->philo_dead = 1;
			data->philo[i].dead = 1;
			return (0);
		}
		i = (i + 1) % data->number;
	}
	return (1);
}

void	*monitor(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (!data->philo_dead)
	{
		if (!check_philo_alive(data))
			break ;
	}
	return (NULL);
}

int	ft_print(t_data *data, int id, char *status)
{
	long long	now;

	pthread_mutex_lock(&data->write_mutex);
	now = t_time(data->start_time);
	printf("%lld  %d  %s\n", now, id, status);
	if (!data->philo_dead)
		pthread_mutex_unlock(&data->write_mutex);
	return (1);
}
