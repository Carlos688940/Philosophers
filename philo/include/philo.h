#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>

#define INIT 1
#define LOCK 2
#define UNLOCK 3

typedef struct s_data
{
	bool		dead_flag;
        int		n_philos;
	int		n_time_to_eat;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	size_t		start_time;
	pthread_mutex_t	*forks;
	struct	s_philo	*philos;
	struct timeval	tv;
}	t_data;

typedef	struct s_philo
{
	pthread_t	*thread;
	int		id;
	long		last_meal;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct	s_data	*data;
}	t_philo;

/* -------------------------------------------------------------------------- */
/*                                    Utils                                   */
/* -------------------------------------------------------------------------- */
int	ft_isdigit(int c);
int	ft_strlen(const char *s);
int	ft_atoi(const char *str);
int	print_error(char *s);

/* -------------------------------------------------------------------------- */
/*                                   Syntax                                   */
/* -------------------------------------------------------------------------- */
int	check_syntax(char *s);
int	check_input(int ac, char **av);

#endif