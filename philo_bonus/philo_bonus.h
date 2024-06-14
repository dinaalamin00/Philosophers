/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:23:58 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/05 11:45:04 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define SUCCESS 0
# define FAILURE 1
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/wait.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/time.h>

typedef struct s_arg
{
	long				philo_no;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	int					no_meals;
	sem_t				*fork;
	sem_t				*meal;
	sem_t				*print;
	sem_t				*alive;
}	t_arg;

typedef struct s_data
{
	long				philo_no;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	int					no_meals;
	int					id;
	pid_t				pid;
	int					status;
	int					eaten;
	long				last_meal;
	sem_t				*fork;
	sem_t				*meal;
	sem_t				*print;
	sem_t				*alive;
	struct timeval		start;
}	t_data;

//utils
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
long	get_time_ms(struct timeval start);

// //parse
int		assign_arg(int ac, char **av, t_arg *arg);
void	print_status(t_data *data, int phd, char *status);

//threads
int		init(t_data *data, t_arg arg);
int		child_process(t_data *data, int phid);
int		open_semaphores(t_arg *arg);
void	close_semaphores(t_arg *arg);

//monitor
int		init_monitor(t_data *data);
void	*monitor(void *vptr);
int		is_dead(t_data *data);
#endif