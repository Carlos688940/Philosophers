/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:29:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/11 15:36:24 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	convert_data(char **input, t_data *data, int ac);
void	data_init(t_data *data);

long	get_time(void);
void	lock_forks(pthread_mutex_t *first, pthread_mutex_t *second);




void	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philos[i].thread, NULL);
}

void	mutex_destroy(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->mtx_init);	
	pthread_mutex_destroy(&data->mtx_end);	
}

void	unset_all(t_data *data)
{
	join_threads(data);
	mutex_destroy(data); 
}

int	main(int ac, char **av)
{
	t_data	data;

	if (check_input(ac, av) < 0)
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (convert_data(av + 1, &data, ac) < 0) //n_philos ,time_die, time_eat, time_sleep, meals_nbr
		return (1); 
	data_init(&data); //forks, philos, end
	unset_all(&data);
	return (0);
}

void	eat(t_philo *philo)
{
	if (philo->id & 1)
		lock_forks(philo->right_fork, philo->left_fork);
	else
		lock_forks(philo->left_fork, philo->right_fork);
	philo->last_meal = get_time();
	ft_usleep(); //TODO create this function
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_init(philo->data);
	while (!check_status(&philo->data->mtx_end, &philo->data->end_status))
	{
		eat(philo);
	}
	return (NULL);
}

void	lock_forks(pthread_mutex_t *first, pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	pthread_mutex_lock(second);
}

void	set_philos(t_data *data)
{
	int	pos;

	pos = -1;
	while (++pos < data->n_philos)
	{
		data->philos[pos].id = pos;
		data->philos[pos].full= 0;
		data->philos[pos].left_fork = &data->forks[pos];
		pthread_mutex_init(data->philos[pos].left_fork, NULL); //init mutex
		data->philos[pos].right_fork = &data->forks[pos + 1 % data->n_philos]; 
		data->philos[pos].data = data;
		pthread_create(&data->philos[pos].thread, NULL, routine, &data->philos[pos]);
	}
} 

long	get_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	data_init(t_data *data)
{
	data->end_status = false;
	data->forks = alloc_mem(sizeof(pthread_mutex_t) * data->n_philos, NULL);
	memset(data->forks, 0, sizeof(pthread_mutex_t) * data->n_philos);
	data->philos = alloc_mem(sizeof(t_philo) * data->n_philos, data);
	memset(data->philos, 0, sizeof(t_philo) * data->n_philos);
	set_philos(data);
	data->start_time = get_time();
	set_bool(&data->mtx_init, &data->ready_status, true);
}
