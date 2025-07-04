/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:32:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/25 16:16:54 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_diff(long diff, t_data *data, t_philo *philo);
bool	all_full(t_philo *philos, int n);
int		check_philos(t_philo *philo, t_data *data);

void	*monitoring(void *info)
{
	t_data	*data;
	t_philo	*philos;
	int		i;

	data = (t_data *)info;
	philos = data->philos;
	i = -1;
	data->start_time = get_time();
	set_bool(&data->mtx_init, &data->ready_status, true);
	while (1)
	{
		++i;
		if (check_philos(&philos[i], data))
			break ;
		if (data->meals_nbr && all_full(philos, data->n_philos))
		{
			set_bool(&data->mtx_end, &data->end_status, true);
			break ;
		}
		if (i == data->n_philos - 1)
		{
			i = -1;
			usleep(100);
		}
	}
	return (NULL);
}

int	check_philos(t_philo *philo, t_data *data)
{
	if (!get_long(&philo->mtx_lst_meal, &philo->lst_meal))
	{
		if (check_diff(get_time() - data->start_time, data, philo))
			return (1);
	}
	else
	{
		if (check_diff(get_time() \
		- get_long(&philo->mtx_lst_meal, &philo->lst_meal), data, philo))
			return (1);
	}
	return (0);
}

bool	all_full(t_philo *philos, int n)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (++i < n)
	{
		if (get_bool(&philos[i].mtx_full, &philos[i].full))
			count++;
	}
	if (count == n)
		return (true);
	return (false);
}

bool	check_diff(long diff, t_data *data, t_philo *philo)
{
	if (get_bool(&philo->mtx_full, &philo->full))
		return (false);
	if (diff > data->time_to_die)
	{
		set_bool(&data->mtx_end, &data->end_status, true);
		print_action(DIE, &data->mtx_print, philo);
		printf(RED"%ld    %d    died\n"RST, get_time() - data->start_time, philo->id);
		return (true);
	}
	return (false);
}
