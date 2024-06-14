/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:23:47 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/05 15:25:42 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_arg			arg;

	if (assign_arg(argc, argv, &arg) == FAILURE)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (open_semaphores(&arg) == FAILURE)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	init(&data, arg);
	close_semaphores(&arg);
	return (0);
}
