/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 20:14:39 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/25 16:27:32 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(t_mtx *mutex, bool *val, bool code)
{
	pthread_mutex_lock(mutex);
	*val = code;
	pthread_mutex_unlock(mutex);
}

void	set_long(t_mtx *mutex, long *var, long val)
{
	pthread_mutex_lock(mutex);
	*var = val;
	pthread_mutex_unlock(mutex);
}

void	lock_forks(t_philo *philo)
{
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
	print_action(FORKS, &philo->data->mtx_print, philo);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	start;
	long	diff;

	(void)philo;
	start = get_time();
	diff = time;
	while (diff > 0)
	{
		usleep(300);
		diff = time - (get_time() - start);
		// if (philo && get_bool(&philo->data->mtx_end, &philo->data->end_status))
		// 	break ;
	}
}
