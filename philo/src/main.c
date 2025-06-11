/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:29:22 by carlaugu          #+#    #+#             */
/*   Updated: 2025/06/11 15:36:24 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	convert_data(char **input, t_data *data, int ac);
void	data_init(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (check_input(ac, av) < 0)
		return (1);
	memset(&data, 0, sizeof(t_data));
	if (convert_data(av + 1, &data, ac) < 0) //n_philos ,time_die, time_eat, time_sleep, meals_nbr
		return (1); 
	data_init(&data); //forks, philos, end
	unset_all(&data);
	return (0);
}

void	print_action(t_action *act, long time, pthread_mutex_t *mtx, t_philo *philo)
{
	pthread_mutex_lock(mtx);
	if (act == EAT)
		printf("%d %d is eating");//TODO add args to priontf
	else if (act == FORKS)
		printf("%d %d has taken a fork");//TODO add args to printf
	else if (act == SLEEP)
		printf("%d %d is sleeping");//TODO add args to printf
	else if (act == THINK)
		printf("%d %d is thinking");//TODO add args to printf
	else if (act == DIE)
		printf("%d %d died");//TODO add args to printf
	pthread_mutex_unlock(mtx);
}

void	eat(t_philo *philo)
{
	//TODO check if is full - return
	philo->last_meal = get_time();
	print_action(FORKS, time, &philo->data->mtx_print, philo);
	print_action(FORKS, time, &philo->data->mtx_print, philo);
	// ft_usleep(); //TODO create this function
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_init(philo->data);
	while (!check_status(&philo->data->mtx_end, &philo->data->end_status))
	{
		lock_forks(philo);
		eat(philo);
		unlock_forks(philo);
	}
	return (NULL);
}
