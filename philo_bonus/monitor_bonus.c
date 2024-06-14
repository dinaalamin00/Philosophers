/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 16:03:36 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/05 15:42:12 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	is_full(t_data *data)
{
	long	current_time;

	current_time = get_time_ms(data->start);
	sem_wait(data->meal);
	if (current_time - data->last_meal > data->t_die)
	{
		sem_post(data->meal);
		return (1);
	}
	sem_post(data->meal);
	return (0);
}

int	is_dead(t_data *data)
{
	sem_wait(data->meal);
	if (get_time_ms(data->start) - data->last_meal > data->t_die)
	{
		sem_post(data->meal);
		return (1);
	}
	sem_post(data->meal);
	return (0);
}

void	*monitor(void *vptr)
{
	t_data	*data;

	data = (t_data *)vptr;
	while (1)
	{
		if (is_dead(data))
		{
			print_status(data, data->id, "died");
			sem_post(data->alive);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

int	init_monitor(t_data *data)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, data) != 0)
	{
		write(2, "thread Error\n", 13);
		return (FAILURE);
	}
	if (pthread_detach(monitor_thread) != 0)
	{
		write(2, "thread Error\n", 13);
		return (FAILURE);
	}
	return (SUCCESS);
}
