/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 07:36:29 by zdasser@stu       #+#    #+#             */
/*   Updated: 2022/05/09 11:01:32 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

void	philo_eat(t_data *data, int i)
{
	pthread_mutex_lock(&data->forks[data->philo[i].left]);
	ft_print(data, data->philo[i].n, "has gotten a left fork");
	pthread_mutex_lock(&data->forks[data->philo[i].right]);
	ft_print(data, data->philo[i].n, "has gotten a right fork");
	data->philo[i].last_time_ate = ft_time();
	ft_print(data, data->philo[i].n, "is eating");
	ft_sleep(data->philo[i].time_eat * 1000);
	drop_forks(data, i);
}

void	philo_sleep(t_data *data, int i)
{
	ft_print(data, data->philo[i].n, "is sleeping");
	ft_sleep(data->philo[i].time_sleep * 1000);
}

void	philo_think(t_data *data, int i)
{
	ft_print(data, data->philo[i].n, "is thinking");
}

void	drop_forks(t_data *data, int i)
{
	pthread_mutex_unlock(&data->forks[data->philo[i].left]);
	pthread_mutex_unlock(&data->forks[data->philo[i].right]);
	data->philo[i].n_times_ate++;
}
