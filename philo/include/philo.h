/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-18 22:32:47 by carlaugu          #+#    #+#             */
/*   Updated: 2025-06-18 22:32:47 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <limits.h>

# define RST	"\033[0m"
# define YLW	"\033[37m"
# define GRN	"\033[32m"
# define BLUE	"\033[34m"
# define ORG	"\033[38;5;208m"
# define RED	"\033[31m" // red

typedef enum s_action
{
	FORKS,
	EAT,
	SLEEP,
	THINK,
	DIE
}	t_action;

typedef struct s_data
{  
	long		n_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_nbr;
	long		start_time;
	bool		end_status; // used to check is simulation ends
	bool		ready_status; // used to check is can start
	bool		fail;
	pthread_mutex_t	mtx_init; // used in wait_init
	pthread_mutex_t	mtx_end; // used in check_status
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_fail;
	pthread_mutex_t	*forks;
	pthread_t	monitor;
	struct	s_philo	*philos;
}	t_data;

typedef	struct s_philo
{
	pthread_t	thread;
	long		last_meal;
	int		id;
	int		meals_count;
	bool		full;
	bool		die;
	bool		starvation;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	mtx_lst_meal;
	pthread_mutex_t	mtx_full;
	pthread_mutex_t	mtx_die;
	struct	s_data	*data;
}	t_philo;


/* -------------------------------------------------------------------------- */
/*                                   Routine                                  */
/* -------------------------------------------------------------------------- */
void	*routine(void *data);
void    *monitoring(void *info);
/* -------------------------------------------------------------------------- */
/*                                    Utils                                   */
/* -------------------------------------------------------------------------- */
int	error_exit(char *s, t_data *data);
long	get_time(void);
void	*alloc_mem(size_t size, t_data *data);
void	free_all(t_data *data);
void	ft_usleep(long time);

/* -------------------------------------------------------------------------- */
/*                                 Mini_libft                                 */
/* -------------------------------------------------------------------------- */
int	ft_strlen(const char *s);
int	ft_isdigit(int c);
long	ft_atol(char *str);
/* -------------------------------------------------------------------------- */
/*                                   Syntax                                   */
/* -------------------------------------------------------------------------- */
int	check_syntax(char *s);
int	check_input(int ac, char **av);

/* -------------------------------------------------------------------------- */
/*                                    Mutex                                   */
/* -------------------------------------------------------------------------- */
bool	get_bool(pthread_mutex_t *mutex, bool *val);
bool	check_status(pthread_mutex_t *mtx, bool *status);
long	get_long(pthread_mutex_t *mutex, long *val);
void	set_long(pthread_mutex_t *mutex, long *var, long val);
void	set_bool(pthread_mutex_t *mutex, bool *val, bool code);
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
void	wait_init(t_data *data);
void	print_action(t_action act, long time, pthread_mutex_t *mtx, t_philo *philo);
/* -------------------------------------------------------------------------- */
/*                                    Init and End                              */
/* -------------------------------------------------------------------------- */
int	convert_data(char **input, t_data *data, int ac);
int	data_init(t_data *data);
void	unset_all(t_data *data, int nbr);

#endif