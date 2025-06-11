/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:19:46 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/11 15:09:46 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_init(t_data *data)
{
	while (!get_bool(&data->check_init, &data->ready))
		;
}

bool	get_bool(pthread_mutex_t *mutex, bool *val)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *val;
	pthread_mutex_unlock(mutex);
	return (res);	
}

void	set_bool(pthread_mutex_t *mutex, bool *val, bool code)
{
	pthread_mutex_lock(mutex);
	*val = code;
	pthread_mutex_unlock(mutex);
}

bool	check_status(pthread_mutex_t *mtx, bool *status)
{
	return (get_bool(mtx, status));
}

long	get_value(pthread_mutex_t *mutex, long *val)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *val;
	pthread_mutex_unlock(mutex);
	return (res);	
}