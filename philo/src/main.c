/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:29:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/26 14:34:22 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	convert_data(char **input, t_data *data, int ac);
void	data_init(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	check_input(ac, av);
	memset(&data, 0, sizeof(t_data));
	convert_data(av + 1, &data, ac); //n_philos ,time_die, time_eat, time_sleep, meals_nbr
	data_init(&data); //forks, philos, end
	return (0);
}

void	data_init(t_data *data)
{
	data->end =false;
	data->forks = alloc_mem(sizeof(pthread_mutex_t) * data->n_philos, NULL);
	data->philos = alloc_mem(sizeof(t_philo) * data->n_philos, data);
}


