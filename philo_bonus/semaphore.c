/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:19:25 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/09 10:45:52 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	open_semaphores(t_arg *arg)
{
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("meal");
	sem_unlink("alive");
	if (arg->philo_no == 1)
		arg->fork = sem_open("fork", O_CREAT, 0644, arg->philo_no);
	else
		arg->fork = sem_open("fork", O_CREAT, 0644, arg->philo_no / 2);
	arg->print = sem_open("print", O_CREAT, 0644, 1);
	arg->meal = sem_open("meal", O_CREAT, 0644, 1);
	arg->alive = sem_open("alive", O_CREAT, 0644, 0);
	if (arg->fork == SEM_FAILED || arg->print == SEM_FAILED
		|| arg->meal == SEM_FAILED || arg->alive == SEM_FAILED)
	{
		printf("fork sem\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	close_semaphores(t_arg *arg)
{
	sem_close(arg->fork);
	sem_close(arg->print);
	sem_close(arg->alive);
	sem_close(arg->meal);
	sem_unlink("fork");
	sem_unlink("print");
	sem_unlink("meal");
	sem_unlink("alive");
}
