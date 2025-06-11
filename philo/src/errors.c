/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:14:44 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/11 13:35:43 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_exit(char *s, t_data *data)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	if (data)
		free_all(data);
	return (-1);
}
