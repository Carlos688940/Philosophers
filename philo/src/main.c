/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:29:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/22 12:32:16 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_data_and_init(char **input, t_data *data, int ac);
int	init_mutex(t_data *data);
int	reset_data(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (check_input(ac, av) < 0)
		return (1);
	if (get_data_and_init(av + 1, &data, ac) < 0)
		return (1);
	if (reset_data(&data) < 0)
		return (1);	
	// routine();///////////////////
	return (0);
}

// void	routine()
// {
// 	while ()
// }

int	get_data_and_init(char **input, t_data *data, int ac)
{	
	memset(data, 0,sizeof(t_data));
	data->n_philos = ft_atoi(input[0]);
	if (data->n_philos == 0)
		return (print_error("Error: number of philosophers must be at least 1\n"));
	data->time_to_die = ft_atoi(input[1]);
	data->time_to_eat = ft_atoi(input[2]);
	data->time_to_sleep = ft_atoi(input[3]);
	if (ac == 6)
		data->n_time_to_eat = ft_atoi(input[4]);
	data->forks = malloc(data->n_philos * sizeof(pthread_mutex_t));
	if (!data->forks)
		return (print_error("Cannot allocate memory\n"));
	if (init_mutex(data) < 0)
	{
		free (data->forks);
		return (-1);
	}
	gettimeofday(&data->tv, NULL); 
	data->start_time = data->tv.tv_sec * 1000 + data->tv.tv_usec / 1000;
	printf("start time: %ld\n", data->start_time);/////////////////////////////////////// delete
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) < 0)
			return (print_error("Error: pthread_mutex_init\n"));
	}
	return (0);
}

int	reset_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]) < 0)
			return (print_error("Error: pthread_mutex_destroy\n"));
	}
	free(data->forks);
	return (0);
}
