/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:32:52 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/09 10:56:58 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_forks(t_philo *p)
{
	t_data	*data;

	data = p->data;
	pthread_mutex_lock(&data->fork[p->right_fork]);
	pthread_mutex_lock(&data->fork[p->left_fork]);
	if (*p->left_val == p->id || *p->right_val == p->id)
	{
		pthread_mutex_unlock(&data->fork[p->left_fork]);
		pthread_mutex_unlock(&data->fork[p->right_fork]);
		return (0);
	}
	return (1);
}

void	sub_routine(t_philo *p)
{
	t_data	*data;

	data = p->data;
	if (free_forks(p))
	{
		print_status(p, "has taken a fork");
		print_status(p, "has taken a fork");
		print_status(p, "is eating");
		pthread_mutex_lock(&data->meal_time);
		p->last_meal = get_time_ms(data->start);
		p->meal_no++;
		pthread_mutex_unlock(&data->meal_time);
		ft_usleep(p, data->t_eat);
		*p->left_val = p->id;
		*p->right_val = p->id;
		pthread_mutex_unlock(&data->fork[p->left_fork]);
		pthread_mutex_unlock(&data->fork[p->right_fork]);
		print_status(p, "is sleeping");
		ft_usleep(p, data->t_sleep);
		print_status(p, "is thinking");
	}
}

void	*routine(void *vptr)
{
	t_data	*data;
	t_philo	*p;

	p = (t_philo *)vptr;
	data = p->data;
	if (p->id % 2 == 0)
		usleep(data->t_eat);
	while (1)
	{
		if (!all_alive(data, p))
			break ;
		if (data->philo_no == 1)
		{
			print_status(p, "has taken a fork");
			usleep(data->t_die * 1000);
			break ;
		}
		sub_routine(p);
	}
	return (NULL);
}

int	init_forks(t_data *data)
{
	int	i;

	data->fork_var = malloc (data->philo_no * sizeof(int));
	if (!data->fork_var)
	{
		free(data->fork);
		return (FAILURE);
	}
	i = 0;
	while (i < data->philo_no)
	{
		data->fork_var[i] = -1;
		i++;
	}
	return (SUCCESS);
}

void	init_thread(t_data *data)
{
	if (init_forks(data) == FAILURE)
		return ;
	gettimeofday(&data->start, NULL);
	data->p = malloc((data->philo_no) * sizeof(t_philo));
	if (!data->p)
	{
		free(data->fork_var);
		return ;
	}
	init_philo(data);
	if (creat_threads(data) == FAILURE)
	{
		free(data->fork_var);
		return ;
	}
	if (join_threads(data) == FAILURE)
	{
		free(data->fork_var);
		return ;
	}
	free(data->fork_var);
	free(data->p);
	return ;
}
