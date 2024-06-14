/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 12:01:57 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/09 10:33:34 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

static void	checksign(char c, int *i, int *sign)
{
	if (c == '+' || c == '-')
	{
		if (c == '-')
			*sign *= -1;
		(*i)++;
	}
}

int	ft_atoi(const char *nptr)
{
	int			sign;
	long		result;
	int			i;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	checksign(nptr[i], &i, &sign);
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		if ((nptr[i] - '0' > (LONG_MAX % 10) && (result == (LONG_MAX / 10)))
			|| result > (LONG_MAX / 10))
		{
			if (sign == 1)
				return (-1);
			if (sign == -1)
				return (0);
		}
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	return (result * sign);
}

int	valid_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j] == 32 && av[i][j])
			j++;
		if (av[i][j] == '+' || av[i][j] == '-')
			j++;
		while (av[i][j] >= '0' && av[i][j] <= '9' && av[i][j])
			j++;
		while (av[i][j] == 32 && av[i][j])
			j++;
		if (av[i][j])
			return (0);
		i++;
	}
	return (1);
}

int	assign_arg(int ac, char **av, t_arg *arg)
{
	ft_bzero(arg, sizeof(t_arg));
	if (ac < 5 || ac > 6)
		return (FAILURE);
	if (!valid_arg(av))
		return (FAILURE);
	arg->philo_no = ft_atoi(av[1]);
	arg->t_die = ft_atoi(av[2]);
	arg->t_eat = ft_atoi(av[3]);
	arg->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->no_meals = ft_atoi(av[5]);
	else
		arg->no_meals = -1;
	if (arg->philo_no < 1 || arg->t_die <= 0
		|| arg->t_eat <= 0 || arg->t_sleep <= 0)
		return (FAILURE);
	if (ac == 6 && arg->no_meals <= 0)
		return (FAILURE);
	return (SUCCESS);
}
