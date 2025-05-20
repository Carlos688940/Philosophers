/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:29:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/05/20 14:25:01 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_syntax(char *s)
{
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (print_syntax_errors("Only numeric inputs are allowed!\n"));
		s++;
	}
	return (0);	
}

int	check_input(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (print_syntax_errors("Wrong number of arguments! Program needs 4 or 5 arguments!\n"));
	while (av[++i])
	{
		if (check_syntax(av[i]) < 0)
			return (-1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (check_input(ac, av) < 0)
		return (1);
	return (0);
}