/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:13:12 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/25 16:28:01 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	get_bool(t_mtx *mutex, bool *val)
{
	bool	res;

	pthread_mutex_lock(mutex);
	res = *val;
	pthread_mutex_unlock(mutex);
	return (res);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

long	get_long(t_mtx *mutex, long *val)
{
	long	res;

	pthread_mutex_lock(mutex);
	res = *val;
	pthread_mutex_unlock(mutex);
	return (res);
}

bool	check_status(t_mtx *mtx, bool *status)
{
	return (get_bool(mtx, status));
}

void	wait_init(t_data *data)
{
	while (!get_bool(&data->mtx_init, &data->ready_status))
		usleep(1);
}
