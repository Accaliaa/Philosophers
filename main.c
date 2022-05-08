/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 06:39:30 by zdasser@stu       #+#    #+#             */
/*   Updated: 2022/05/08 14:59:35 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_data(char **argv, int argc)
{
	if(ft_atoi(argv[1]) == 0)
		return(0);
	if(ft_atoi(argv[2]) < 1 || ft_atoi(argv[3]) < 1 || ft_atoi(argv[4]) < 1)
		return(0);
	if(argc == 6 && ft_atoi(argv[5]) < 1)
		return(0);
	return(1);	
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
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




void	join_and_free_philos(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->number)
	{
		pthread_join(data->philo[i].thread, NULL);
		pthread_mutex_destroy(&data->philo[i++].check_mutex);
	}
	free(data->philo);
	i = 0;
	while (i < data->number)
		pthread_mutex_destroy(&data->forks[i++]);
	free(data->forks);
}

void    parsing_data(int argc, char **argv, t_data *data)
{
    int i;

    i = 0;
    if(argc == 6)
        data->n_of_time_to_eat = ft_atoi(argv[5]);
    while(i < data->number)
    {
    data->philo[i].num = ft_atoi(argv[1]);
    data->philo[i].n = i + 1;
    data->philo[i].time_die = ft_atoi(argv[2]);
    data->philo[i].time_eat = ft_atoi(argv[3]);
    data->philo[i].time_sleep = ft_atoi(argv[4]);
	data->philo[i].n_times_ate = 0;
	data->philo[i].dead = 0;
    if(argc == 6)
        data->philo[i].n_toeat = ft_atoi(argv[5]);
    i++;
    }
}

void	action_philos(t_data *data)
{
	int	i;

	data->philo_dead = 0;
	data->Time = ft_time();
	if (pthread_mutex_init(&data->finish_mutex, NULL) != 0)
		return ;
	i = 0;
	while (i < data->number)
	{
		data->n_thread = i;
		pthread_create(&data->philo[i].thread,NULL, &philo, (void *) data);
		i += 2;
		ft_sleep(20);
	}
	ft_sleep(50);
	i = 1;
	while (i < data->number)
	{
		data->n_thread = i;
		pthread_create(&data->philo[i].thread,NULL, &philo, (void *) data);
		i += 2;
		ft_sleep(20);
	}
	pthread_create(&data->monitor, NULL, &monitor, (void *) data);
	join_threads(data);
	return;
}

void    init_data(t_data *data)
{
    int i;

    i = 0;
    pthread_mutex_init(&data->finish_mutex, NULL);
	data->forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * data->number);
    data->philo = (t_philo*)malloc(sizeof(t_philo) * data->number);
    if(!data->forks || !data->philo)
        return;
    while(i < data->number)
    {
        pthread_mutex_init(&data->philo[i].check_mutex, NULL);
        pthread_mutex_init(&data->forks[i], NULL);
		data->philo[i].left = i;
		data->philo[i].right = i + 1;
		if(i ==  data->number - 1)
			data->philo[i].right = 0;
		i++;
    }
    
    
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

int main(int argc, char **argv)
{
    t_data data;

    if(argc < 5 || argc > 6)
        printf("error arguments\n");
    else
    {
        data.number = ft_atoi(argv[1]);
        init_data(&data);
        parsing_data(argc, argv, &data);
        if(!check_data(argv, argc))
		{
			printf("error\n");
			return(0);
		}
        
        action_philos(&data);
        destroy_threads(&data);

    }
    return(0);
}