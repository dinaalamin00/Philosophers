/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:00:37 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/09 10:52:00 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	eat_sleep(t_data *data, int phid)
{
	sem_wait(data->fork);
	print_status(data, phid, "has taken a fork");
	print_status(data, phid, "has taken a fork");
	print_status(data, phid, "is eating");
	sem_wait(data->meal);
	data->last_meal = get_time_ms(data->start);
	data->eaten++;
	sem_post(data->meal);
	usleep(data->t_eat * 1000);
	sem_post(data->fork);
	print_status(data, phid, "is sleeping");
	usleep(data->t_sleep * 1000);
	print_status(data, phid, "is thinking");
	return (1);
}

int	child_process(t_data *data, int phid)
{
	if (init_monitor(data) == FAILURE)
	{
		sem_post(data->alive);
		return (FAILURE);
	}
	if (phid % 2 == 0)
		usleep(data->t_eat * 1000);
	if (data->philo_no == 1)
	{
		sem_wait(data->fork);
		print_status(data, phid, "has taken a fork");
		usleep(data->t_die * 1000);
		print_status(data, phid, "died");
		sem_post(data->alive);
		exit (1);
	}
	while (data->no_meals == -1 || data->eaten < data->no_meals)
	{
		if (!eat_sleep(data, phid))
			break ;
	}
	sem_post(data->alive);
	exit (0);
	return (SUCCESS);
}
