/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdasser <zdasser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:16:50 by zdasser           #+#    #+#             */
/*   Updated: 2022/05/09 14:59:17 by zdasser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

long long	t_time(long long time)
{
	if (time > 0)
		return (ft_time() - time);
	return (0);
}

void	ft_sleep(int j)
{
	long	start;

	start = ft_time();
	usleep((j * 90) / 100);
	while (ft_time() - start < j / 1000)
		usleep(100);
}

long long	ft_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_atoi(char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (n < 0 || ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
		|| n > 2147483647)
		return (0);
	return (n);
}
