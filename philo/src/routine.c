/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine,c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 09:14:26 by carlaugu          #+#    #+#             */
/*   Updated: 2025-06-12 09:14:26 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_init(philo->data);
	if (get_bool(&philo->data->mtx_fail, &philo->data->fail))
		return (NULL);
	while (!check_status(&philo->data->mtx_end, &philo->data->end_status))
	{
		lock_forks(philo);
		eating(philo);
		unlock_forks(philo);
		if (philo->full)
			break;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	ft_usleep(long time, t_philo *philo)
{
	long	start;
	long	diff;

	start = get_time();
	diff = time;
	while (diff > 0 && !get_bool(&philo->mtx_die, &philo->die))
	{
		if (diff > 100)
			usleep(100 * 1000);
		else
			usleep(diff * 1000);
		diff = time - (get_time() - start);
	}
	if (get_bool(&philo->mtx_die, &philo->die)) ////////delete
		printf("morri no usleep\n");
}

void	thinking(t_philo *philo)
{
	long	time;

	if (get_bool(&philo->data->mtx_end, &philo->data->end_status))
		return;
	time = get_time() - philo->data->start_time;
	print_action(THINK, time, &philo->data->mtx_print, philo);
	ft_usleep(1, philo);
}

void	sleeping(t_philo *philo)
{
	long	time;

	if (get_bool(&philo->data->mtx_end, &philo->data->end_status))
		return;
	time = get_time() - philo->data->start_time;
	print_action(SLEEP, time, &philo->data->mtx_print, philo);
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	eating(t_philo *philo)
{
	long	time;

	if (get_bool(&philo->data->mtx_end, &philo->data->end_status))
		return;
	philo->meals_count++;
	time = get_time();
        set_long(&philo->mtx_lst_meal, &philo->last_meal, time);
	time = time - philo->data->start_time;
	print_action(EAT, time, &philo->data->mtx_print, philo);
	ft_usleep(philo->data->time_to_eat, philo);
	if (philo->data->meals_nbr && philo->meals_count == philo->data->meals_nbr)
		set_bool(&philo->mtx_full, &philo->full, true);
}
