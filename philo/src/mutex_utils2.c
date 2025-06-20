/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-11 20:14:39 by carlaugu          #+#    #+#             */
/*   Updated: 2025-06-11 20:14:39 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *val, bool code)
{
	pthread_mutex_lock(mutex);
	*val = code;
	pthread_mutex_unlock(mutex);
}

void	set_long(pthread_mutex_t *mutex, long *var, long val)
{
	pthread_mutex_lock(mutex);
	*var = val;
	pthread_mutex_unlock(mutex);
}

void	lock_forks(t_philo *philo)
{
	long	time;

	if (philo->id & 1)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	if (get_bool(&philo->data->mtx_end, &philo->data->end_status))
		return;
	time = get_time() - philo->data->start_time;
	print_action(FORKS, time, &philo->data->mtx_print, philo);
	time = get_time()- philo->data->start_time;
	print_action(FORKS, time, &philo->data->mtx_print, philo);
}