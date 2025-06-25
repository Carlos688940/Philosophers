/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:18:42 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/25 16:08:12 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int		set_philos(t_data *data);
void	init_general_mutex(t_data *data);

int	convert_data(char **input, t_data *data, int ac)
{
	memset(data, 0, sizeof(t_data));
	data->n_philos = ft_atol(input[0]);
	if (data->n_philos == 0)
		return (error_exit("Error: number of philosophers must"
				"be at least 1\n", NULL));
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
		return (error_exit("Some value is too big,"
				"INT_MAX is the limit!\n", NULL));
	if (data->time_to_die == 0 || data->time_to_eat == 0 \
		|| data->time_to_sleep == 0)
		return (-1);
	return (0);
}

int	mono_philo(t_data *data)
{
	data->start_time = get_time();
	printf(ORG"%ld 1 has taken a fork\n"RST, get_time() - data->start_time);
	ft_usleep(data->time_to_die, NULL);
	printf(RED"%ld 1 died\n"RST, get_time() - data->start_time);
	return (0);
}

int	data_init(t_data *data)
{
	if (data->n_philos == 1)
		return (mono_philo(data));
	data->forks = alloc_mem(sizeof(t_mtx) * data->n_philos, NULL);
	memset(data->forks, 0, sizeof(t_mtx) * data->n_philos);
	data->philos = alloc_mem(sizeof(t_philo) * data->n_philos, data);
	memset(data->philos, 0, sizeof(t_philo) * data->n_philos);
	init_general_mutex(data);
	if (set_philos(data) < 0)
		return (-1);
	if (pthread_create(&data->monitor, NULL, monitoring, data) != 0)
	{
		set_bool(&data->mtx_fail, &data->fail, true);
		unset_all(data, data->n_philos);
		return (-1);
	}
	return (0);
}

void	init_general_mutex(t_data *data)
{
	pthread_mutex_init(&data->mtx_init, NULL);
	pthread_mutex_init(&data->mtx_end, NULL);
	pthread_mutex_init(&data->mtx_print, NULL);
	pthread_mutex_init(&data->mtx_fail, NULL);
}

int	set_philos(t_data *data)
{
	int	pos;

	pos = -1;
	while (++pos < data->n_philos)
	{
		pthread_mutex_init(&data->forks[pos], NULL);
		data->philos[pos].id = pos + 1;
		data->philos[pos].full = 0;
		data->philos[pos].left_fork = &data->forks[pos];
		data->philos[pos].right_fork = &data->forks[(pos + 1) % data->n_philos];
		data->philos[pos].data = data;
		pthread_mutex_init(&data->philos[pos].mtx_lst_meal, NULL);
		pthread_mutex_init(&data->philos[pos].mtx_full, NULL);
		if (pthread_create(&data->philos[pos].thread, NULL, \
			routine, &data->philos[pos]) != 0)
		{
			set_bool(&data->mtx_fail, &data->fail, true);
			unset_all(data, pos);
			return (-1);
		}
	}
	return (0);
}
