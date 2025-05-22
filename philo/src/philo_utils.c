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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	check_syntax(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != '+')
			return (print_error("Error: only numeric inputs and positive numbers are allowed !\n"));
		s++;
	}
	return (0);	
}

int	check_input(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (print_error("Error: wrong number of arguments. Program needs 4 or 5 arguments!\n"));
	while (av[++i])
	{
		if (check_syntax(av[i]) < 0)
			return (-1);
	}
	return (0);
}