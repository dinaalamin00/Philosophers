/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:17:42 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/05 11:47:09 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data, t_philo *p)
{
	long	current_time;

	pthread_mutex_lock(&data->meal_time);
	current_time = get_time_ms(data->start) - p->last_meal;
	if (current_time > data->t_die)
	{
		pthread_mutex_unlock(&data->meal_time);
		return (1);
	}
	pthread_mutex_unlock(&data->meal_time);
	return (0);
}

int	one_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_no)
	{
		if (is_dead(data, &data->p[i]))
		{
			print_status(&data->p[i], "died");
			pthread_mutex_lock(&data->alive);
			*data->p->dead = 1;
			pthread_mutex_unlock(&data->alive);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_full(t_data *data)
{
	int		i;

	i = 0;
	if (data->no_meals == -1)
		return (0);
	while (i < data->philo_no)
	{
		pthread_mutex_lock(&data->meal_time);
		if (data->p[i].meal_no < data->no_meals)
		{
			pthread_mutex_unlock(&data->meal_time);
			return (0);
		}
		pthread_mutex_unlock(&data->meal_time);
		i++;
	}
	pthread_mutex_lock(&data->alive);
	data->dead = 1;
	pthread_mutex_unlock(&data->alive);
	return (1);
}

void	*check_dead(void *vptr)
{
	t_data	*data;

	data = (t_data *)vptr;
	while (1)
	{
		if (one_dead(data))
			break ;
		if (all_full(data))
			break ;
	}
	return (NULL);
}
