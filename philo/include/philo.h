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

typedef enum s_code
{
	INIT,
	LOCK ,
	UNLOCK,
	DESTROY
}	t_code;

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
	pthread_mutex_t	mtx_init; // used in wait_init
	pthread_mutex_t	mtx_end; // used in check_status
	pthread_mutex_t	*forks;
	struct	s_philo	*philos;
}	t_data;

typedef	struct s_philo
{
	pthread_t	thread;
	long		last_meal;
	int		id;
	int		meals_count;
	int		full;  
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct	s_data	*data;
}	t_philo;

/* -------------------------------------------------------------------------- */
/*                                    Utils                                   */
/* -------------------------------------------------------------------------- */
bool	get_bool(pthread_mutex_t *mutex, bool *val);
bool	check_status(pthread_mutex_t *mtx, bool *status);
int	ft_isdigit(int c);
int	ft_strlen(const char *s);
int	error_exit(char *s, t_data *data);
long	ft_atol(char *str);
long	get_value(pthread_mutex_t *mutex, long *val);
void	*alloc_mem(size_t size, t_data *data);
void	free_all(t_data *data);
void	handle_mutex(pthread_mutex_t *mutex, t_code code);
void	wait_init(t_data *data);
void	set_bool(pthread_mutex_t *mutex, bool *val, bool code);

/* -------------------------------------------------------------------------- */
/*                                   Syntax                                   */
/* -------------------------------------------------------------------------- */
int	check_syntax(char *s);
int	check_input(int ac, char **av);

#endif