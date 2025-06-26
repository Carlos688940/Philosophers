/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 09:14:26 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/25 16:26:46 by carlaugu         ###   ########.fr       */
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
	if (!(philo->id & 1))
		thinking(philo);
	while (!check_status(&philo->data->mtx_end, &philo->data->end_status))
	{
		lock_forks(philo);
		eating(philo);
		unlock_forks(philo);
		if (get_bool(&philo->mtx_full, &philo->full))
			break;
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

void	eating(t_philo *philo)
{
	if (get_bool(&philo->data->mtx_end, &philo->data->end_status))
		return ;
	philo->meals_count++;
	print_action(EAT, &philo->data->mtx_print, philo);
	set_long(&philo->mtx_lst_meal, &philo->lst_meal, get_time());
	ft_usleep(philo->data->time_to_eat, philo);
	if (philo->data->meals_nbr && philo->meals_count == philo->data->meals_nbr)
		set_bool(&philo->mtx_full, &philo->full, true);
}

void	sleeping(t_philo *philo)
{
	if (get_bool(&philo->data->mtx_end, &philo->data->end_status))
		return ;
	print_action(SLEEP, &philo->data->mtx_print, philo);
	ft_usleep(philo->data->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	long	time;

	if (get_bool(&philo->data->mtx_end, &philo->data->end_status))
		return ;
	print_action(THINK, &philo->data->mtx_print, philo);
	if (philo->data->time_to_die - (philo->data->time_to_eat + philo->data->time_to_sleep) > 0)
	{
		time = (philo->data->time_to_die - (philo->data->time_to_eat + philo->data->time_to_sleep)) / 2;
		ft_usleep(time, philo);
	}
	else
		usleep(50);
}
