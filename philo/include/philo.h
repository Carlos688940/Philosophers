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

#define INIT 1
#define LOCK 2
#define UNLOCK 3

typedef struct s_data
{  
	long		n_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_nbr;
	long		start_time;
	bool		end;
	pthread_mutex_t	*forks;
	struct	s_philo	*philos;
	struct timeval	tv;
}	t_data;

typedef	struct s_philo
{
	pthread_t	*thread;
	int		id;
	long		last_meal;
	int		meals_count;
	bool		full;  
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct	s_data	*data;
}	t_philo;

/* -------------------------------------------------------------------------- */
/*                                    Utils                                   */
/* -------------------------------------------------------------------------- */
int	ft_isdigit(int c);
int	ft_strlen(const char *s);
long	ft_atol(char *str);
void	*alloc_mem(size_t size, t_data *data);
void	error_exit(char *s, t_data *data);
void	free_all(t_data *data);

/* -------------------------------------------------------------------------- */
/*                                   Syntax                                   */
/* -------------------------------------------------------------------------- */
void	check_syntax(char *s);
void	check_input(int ac, char **av);

#endif