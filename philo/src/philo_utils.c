/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:59:54 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/22 09:29:06 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_syntax(char *s);

void	check_input(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		error_exit("Error: wrong number of arguments. Program needs 4 or 5 arguments!\n", NULL);
	while (av[++i])
		check_syntax(av[i]);
}

void	check_syntax(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != '+')
			error_exit("Error: only numeric inputs and positive numbers are allowed !\n", NULL);
		s++;
	}
}

void	convert_data(char **input, t_data *data, int ac)
{
	data->n_philos = ft_atol(input[0]);
	if (data->n_philos == 0)
		error_exit("Error: number of philosophers must be at least 1\n", NULL);
	data->time_to_die = ft_atol(input[1]);
	data->time_to_eat = ft_atol(input[2]);
	data->time_to_sleep = ft_atol(input[3]);
	if (ac == 6)
		data->meals_nbr = ft_atol(input[4]);
	if (data->n_philos > INT_MAX || data->time_to_die > INT_MAX 
			|| data->time_to_eat > INT_MAX || data->time_to_sleep > INT_MAX 
			|| data->meals_nbr > INT_MAX)
		error_exit("Some value is too big, INT_MAX is the limit!\n", NULL);
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