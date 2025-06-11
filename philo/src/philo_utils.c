/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:59:54 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/11 13:48:11 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_input(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (error_exit("Error: wrong number of arguments. Program needs 4 or 5 arguments!\n", NULL));
	while (av[++i])
	{
		if (check_syntax(av[i]) < 0)
			return (-1);
	}
	return (0);
}

int	check_syntax(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != '+')
			return (error_exit("Error: only numeric inputs and positive numbers are allowed !\n", NULL));
		s++;
	}
	return (0);
}

int	convert_data(char **input, t_data *data, int ac)
{
	data->n_philos = ft_atol(input[0]);
	if (data->n_philos == 0)
		return (error_exit("Error: number of philosophers must be at least 1\n", NULL));
	data->time_to_die = ft_atol(input[1]);
	data->time_to_eat = ft_atol(input[2]);
	data->time_to_sleep = ft_atol(input[3]);
	if (ac == 6)
	{
		data->meals_nbr = ft_atol(input[4]);
		if (data->meals_nbr == 0)
			return (-1);
	}
	if (data->n_philos > INT_MAX || data->time_to_die > INT_MAX 
			|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX 
			|| data->meals_nbr > INT_MAX)
		return (error_exit("Some value is too big, INT_MAX is the limit!\n", NULL));
	return (0);
}

void	handle_mutex(pthread_mutex_t *mutex, t_code code)
{
	if (code == LOCK)
		pthread_mutex_lock(mutex);
	else if (code == UNLOCK)
		pthread_mutex_unlock(mutex);
	else if (code == INIT)
		pthread_mutex_init(mutex, NULL);
	else if (code == DESTROY)
		pthread_mutex_destroy(mutex);
	else
		write(2, "Error: wrong code\n", ft_strlen("Error: wrong code\n"));
}

void	free_all(t_data *data)
{
	free(data->forks);
	free(data->philos);
}

void	*alloc_mem(size_t size, t_data *data)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit("Error: malloc failed\n", data);
	return (ptr);
}
 