/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:28:18 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/05 11:44:21 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time_ms(struct timeval start)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((current_time.tv_sec - start.tv_sec) * 1000)
		+ ((current_time.tv_usec - start.tv_usec) / 1000));
}

void	print_status(t_data *data, int phid, char *status)
{
	sem_wait(data->print);
	printf("%ld philo %d %s\n", get_time_ms(data->start), phid, status);
	if (*status != 'd')
		sem_post(data->print);
}
