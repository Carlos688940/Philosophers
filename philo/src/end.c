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

void	mutex_destroy(t_data *data, int nbr);
void	join_threads(t_data *data, int nbr);

void	unset_all(t_data *data, int nbr)
{
	join_threads(data, nbr);
	mutex_destroy(data, nbr);
        free_all(data);
}

void	mutex_destroy(t_data *data, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].mtx_lst_meal);
	}
	if (nbr == data->n_philos)
	{
		pthread_mutex_destroy(&data->mtx_init);	
		pthread_mutex_destroy(&data->mtx_end);
		pthread_mutex_destroy(&data->mtx_print);
	}
}

void	join_threads(t_data *data, int nbr)
{
	int	i;

	i = -1;
	while (++i < nbr)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(data->monitor, NULL);
}