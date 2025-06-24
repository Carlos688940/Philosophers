/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:29:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/24 12:57:14 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	convert_data(char **input, t_data *data, int ac);
int	data_init(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (check_input(ac, av) < 0)
		return (1);
	if (convert_data(av + 1, &data, ac) < 0)
		return (1);
	if (data_init(&data) < 0)
		return (1);
	unset_all(&data, data.n_philos);
	return (0);
}

void	print_action(t_action act, long time, t_mtx *mtx, t_philo *philo)
{
	pthread_mutex_lock(mtx);
	if (act == DIE)
		printf(RED"%ld %d died\n"RST, time, philo->id);
	if (!get_bool(&philo->data->mtx_end, &philo->data->end_status))
	{
		if (act == EAT)
			printf(GRN"%ld %d is eating\n"RST, time, philo->id);
		else if (act == FORKS)
			printf(ORG"%ld %d has taken a fork\n"RST, time, philo->id);
		else if (act == SLEEP)
			printf(BLUE"%ld %d is sleeping\n"RST, time, philo->id);
		else if (act == THINK)
			printf(YLW"%ld %d is thinking\n"RST, time, philo->id);
	}
	pthread_mutex_unlock(mtx);
}
