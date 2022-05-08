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
	t_data *data;
	int	i;

	data = (t_data*)par;
	i = data->n_thread;
	pthread_mutex_lock(&data->finish_mutex);
	if (data->philo_dead == 0)
	{	pthread_mutex_unlock(&data->finish_mutex);
		while(data->philo_dead == 0)
		{
			//printf("---%i--h\n", i);
			if(data->philo[i].n_times_ate == data->philo[i].n_toeat )
				{//printf("hello\n");
					return(0);}
			philo_eat(data, i);
			philo_sleep(data, i);
			philo_think(data, i);
			
		}}
	// }if(data->philo[i].n_times_ate == data->n_of_time_to_eat || data->philo_dead)
	// 			{
	// 				return(0);}
	//pthread_mutex_unlock(&data->finish_mutex);
	return(NULL);
}

void	check_philo_alive(t_data *data)
{
	int	i;
	int	now;

	i = 0;
	now = ft_time();
	while(i < data->number && data->philo_dead == 0)
	{
		if((now - data->philo[i].last_time_ate) > data->philo[i].time_die)
			{
				ft_print(data, data->philo[i].n, "is dead");
				data->philo_dead = 1;
				data->philo[i].dead = 1;
				return;
			}
		i++;
	}
}
void	*monitor(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while(!data->philo_dead)
	{
		if(data->n_of_time_to_eat)
			break;
		check_philo_alive(data);
	}
	return(NULL);
}

int	ft_print(t_data *main, int id, char *status)
{
	long long	now;

	now = t_time(main->Time);
	if (main->philo_dead)
		return (0);
		printf("%lld  %d  %s\n", now, id, status);
	return (1);
}
