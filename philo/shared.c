/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:26:20 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/05 11:47:21 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *p, char *status)
{
	pthread_mutex_lock(&p->data->print);
	if (all_alive(p->data, p))
	{
		printf("%ld philo %d %s\n", get_time_ms(p->data->start), p->id, status);
	}
	pthread_mutex_unlock(&p->data->print);
}

int	all_alive(t_data *data, t_philo *p)
{
	pthread_mutex_lock(&data->alive);
	if (*(p->dead) == 1)
	{
		pthread_mutex_unlock(&data->alive);
		return (0);
	}
	pthread_mutex_unlock(&data->alive);
	return (1);
}

void	ft_usleep(t_philo *p, long time)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	while (get_time_ms(start) < time)
	{
		if (!all_alive(p->data, p))
			break ;
		usleep (500);
	}
}

long	get_time_ms(struct timeval start)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((current_time.tv_sec - start.tv_sec) * 1000)
		+ ((current_time.tv_usec - start.tv_usec) / 1000));
}
