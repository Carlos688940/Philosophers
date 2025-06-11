/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-11 20:25:05 by carlaugu          #+#    #+#             */
/*   Updated: 2025-06-11 20:25:05 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	mutex_destroy(t_data *data);
void	join_threads(t_data *data);

void	unset_all(t_data *data)
{
	join_threads(data);
	mutex_destroy(data);
        free_all(data);
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

void	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		pthread_join(data->philos[i].thread, NULL);
}