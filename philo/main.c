/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 10:30:28 by diahmed           #+#    #+#             */
/*   Updated: 2024/05/14 16:24:04 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;

	if (assign_arg(argc, argv, &data) == FAILURE
		|| (init_mutex(&data) == FAILURE))
	{
		printf("Error\n");
		return (1);
	}
	init_thread(&data);
	destroy_mutex(&data);
	return (0);
}
