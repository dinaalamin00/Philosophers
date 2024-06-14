/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diahmed <diahmed@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:15:17 by diahmed           #+#    #+#             */
/*   Updated: 2024/06/05 11:48:03 by diahmed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define SUCCESS 0
# define FAILURE 1
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				*left_val;
	int				*right_val;
	int				meal_no;
	long			last_meal;
	bool			*dead;
	bool			full;
	pthread_t		tid;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	long				philo_no;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	int					no_meals;
	bool				dead;
	bool				full;
	int					*fork_var;
	t_philo				*p;
	pthread_t			check;
	pthread_mutex_t		*fork;
	pthread_mutex_t		print;
	pthread_mutex_t		alive;
	pthread_mutex_t		meal_time;
	struct timeval		start;
}	t_data;

//init
int		init_forks(t_data *data);

//shared
void	print_status(t_philo *p, char *status);
int		all_alive(t_data *data, t_philo *p);
long	get_time_ms(struct timeval start);
void	ft_usleep(t_philo *p, long time);
//utils
int		ft_atoi(const char *nptr);
void	ft_bzero(void *s, size_t n);
//parse
int		assign_arg(int ac, char **av, t_data *data);

//init_destroy_create_join
void	init_philo(t_data *data);
int		init_mutex(t_data *data);
int		destroy_mutex(t_data *data);
int		creat_threads(t_data *data);
int		join_threads(t_data *data);

//routine
void	init_thread(t_data *data);
void	*routine(void *vptr);

//monitor
void	*check_dead(void *vptr);
#endif