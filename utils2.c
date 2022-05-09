/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:50:31 by zdasser           #+#    #+#             */
/*   Updated: 2022/05/09 11:54:06 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->monitor, NULL);
	return (1);
}

int	destroy_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->finish_mutex);
	return (1);
}

void	unlock_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		pthread_mutex_unlock(&data->forks[i]);
		i++;
	}
}
