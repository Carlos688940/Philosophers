/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-11 20:18:42 by carlaugu          #+#    #+#             */
/*   Updated: 2025-06-11 20:18:42 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_philos(t_data *data);

int	convert_data(char **input, t_data *data, int ac)
{
	data->n_philos = ft_atol(input[0]);
	if (data->n_philos == 0)
		return (error_exit("Error: number of philosophers must be at least 1\n", NULL));
	data->time_to_die = ft_atol(input[1]);
	data->time_to_eat = ft_atol(input[2]);
	data->time_to_sleep = ft_atol(input[3]);
	if (ac == 6)
	{
		data->meals_nbr = ft_atol(input[4]);
		if (data->meals_nbr == 0)
			return (-1);
	}
	if (data->n_philos > INT_MAX || data->time_to_die > INT_MAX 
			|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX 
			|| data->meals_nbr > INT_MAX)
		return (error_exit("Some value is too big, INT_MAX is the limit!\n", NULL));
	return (0);
}

void	data_init(t_data *data)
{
	data->end_status = false;
	data->forks = alloc_mem(sizeof(pthread_mutex_t) * data->n_philos, NULL);
	memset(data->forks, 0, sizeof(pthread_mutex_t) * data->n_philos);
	data->philos = alloc_mem(sizeof(t_philo) * data->n_philos, data);
	memset(data->philos, 0, sizeof(t_philo) * data->n_philos);
	init_philos(data);
	data->start_time = get_time();
	set_bool(&data->mtx_init, &data->ready_status, true);
}

void	init_philos(t_data *data)
{
	int	pos;

	pos = -1;
	while (++pos < data->n_philos)
	{
		data->philos[pos].id = pos + 1;
		data->philos[pos].full= 0;
		data->philos[pos].left_fork = &data->forks[pos];
		pthread_mutex_init(data->philos[pos].left_fork, NULL); //init mutex
		data->philos[pos].right_fork = &data->forks[pos + 1 % data->n_philos]; 
		data->philos[pos].data = data;
		pthread_create(&data->philos[pos].thread, NULL, routine, &data->philos[pos]);
	}
}
