/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:11:58 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/05 11:46:20 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	data->fork = malloc (data->philo_no * sizeof(pthread_mutex_t));
	if (!data->fork)
		return (FAILURE);
	i = 0;
	while (i < data->philo_no)
	{
		if (pthread_mutex_init(&data->fork[i], NULL) != 0)
		{
			free(data->fork);
			return (FAILURE);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL) != 0
		|| pthread_mutex_init(&data->alive, NULL) != 0
		|| pthread_mutex_init(&data->meal_time, NULL) != 0)
	{
		free(data->fork);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_no)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	free(data->fork);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->alive);
	pthread_mutex_destroy(&data->meal_time);
	return (SUCCESS);
}

int	creat_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_no)
	{
		if (pthread_create(&data->p[i].tid, NULL, &routine, &data->p[i]) != 0)
		{
			write(2, "Error creating a thread\n", 24);
			free(data->p);
			return (FAILURE);
		}
		i++;
	}
	if (pthread_create(&data->check, NULL, &check_dead, data) != 0)
	{
		write(2, "Error creating a thread\n", 24);
		free(data->p);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	join_threads(t_data *data)
{
	int	i;

	if (pthread_join(data->check, NULL) != 0)
	{
		write(2, "Error joining a thread\n", 24);
		free(data->p);
		return (FAILURE);
	}
	i = 0;
	while (i < data->philo_no)
	{
		if (pthread_join(data->p[i].tid, NULL) != 0)
		{
			write(2, "Error joining a thread\n", 24);
			free(data->p);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_no)
	{
		data->p[i].id = i + 1;
		if ((i + 1) % 2 == 0)
		{
			data->p[i].left_fork = i;
			data->p[i].right_fork = (i + 1) % data->philo_no;
		}
		else
		{
			data->p[i].left_fork = (i + 1) % data->philo_no;
			data->p[i].right_fork = i;
		}
		data->p[i].left_val = &data->fork_var[i];
		data->p[i].right_val = &data->fork_var[(i + 1) % data->philo_no];
		data->p[i].last_meal = get_time_ms(data->start);
		data->p[i].meal_no = 0;
		data->p[i].data = data;
		data->p[i].dead = &data->dead;
		i++;
	}
}
