/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:26:59 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/09 10:47:00 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philos(t_data *data, t_arg arg)
{
	int				i;
	struct timeval	start;

	i = 0;
	gettimeofday(&start, NULL);
	while (i < arg.philo_no)
	{
		data[i].start = start;
		data[i].id = i + 1;
		data[i].last_meal = get_time_ms(data[i].start);
		data[i].eaten = 0;
		data[i].no_meals = arg.no_meals;
		data[i].philo_no = arg.philo_no;
		data[i].t_die = arg.t_die;
		data[i].t_eat = arg.t_eat;
		data[i].t_sleep = arg.t_sleep;
		data[i].alive = arg.alive;
		data[i].print = arg.print;
		data[i].meal = arg.meal;
		data[i].fork = arg.fork;
		i++;
	}
}

void	wait_all(t_data *data, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.philo_no)
	{
		waitpid(-1, &data->status, 0);
		i++;
	}
}

void	term_all(t_data *data, t_arg arg)
{
	int	i;

	i = 0;
	while (i < arg.philo_no)
	{
		if (data[i].pid > 0)
		{
			kill(data[i].pid, SIGKILL);
		}
		i++;
	}
}

int	init(t_data *data, t_arg arg)
{
	pid_t			pid;
	int				i;

	data = malloc(arg.philo_no * sizeof(t_data));
	if (!data)
		return (FAILURE);
	init_philos(data, arg);
	i = 0;
	while (i < arg.philo_no)
	{
		pid = fork();
		if (pid < 0)
			return (free(data), FAILURE);
		if (!pid)
		{
			if (child_process(&data[i], i + 1) == FAILURE)
				return (term_all(data, arg), free(data), FAILURE);
		}
		data[i].pid = pid;
		i++;
	}
	sem_wait(data->alive);
	(term_all(data, arg), wait_all(data, arg), free(data));
	return (FAILURE);
}
