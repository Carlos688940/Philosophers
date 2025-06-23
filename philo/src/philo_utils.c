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

void	free_all(t_data *data)
{
	free(data->forks);
	data->forks = NULL;
	free(data->philos);
	data->philos = NULL;
}

void	*alloc_mem(size_t size, t_data *data)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit("Error: malloc failed\n", data);
	return (ptr);
}
 
long	get_time(void)
{
	struct timeval	tv;
	
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
