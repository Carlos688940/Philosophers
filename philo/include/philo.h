#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

typedef struct s_data
{
        int		n_philos;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_time_to_eat;
	pthread_mutex_t	*forks;
}	t_data;

typedef	struct s_philo
{
	int		id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
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