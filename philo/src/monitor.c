/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlaugu <carlaugu@student.42porto.com>    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-17 14:32:01 by carlaugu          #+#    #+#             */
/*   Updated: 2025-06-17 14:32:01 by carlaugu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool    check_diff(long diff, t_data *data, t_philo *philo);

void    *monitoring(void *info)
{
        int     i;
        t_data  *data;
        t_philo *philos;

        data = (t_data *)info;
        philos = data->philos;
        i = -1;
        wait_init(data);
        while (!get_bool(&data->mtx_end, &data->end_status))
        {
                ++i;
                if (!get_long(&philos[i].mtx_lst_meal, &philos[i].last_meal))
                {
                        if (check_diff(get_time() - data->start_time, data, &philos[i]))
                                break;
                }
                else
                {
                        if (check_diff(get_time() - get_long(&philos[i].mtx_lst_meal, &philos[i].last_meal), data, &philos[i]))
                                break;
                }
                //TODO tenho que fazer algo para verificar se todos estao cheios senao o monitor
                // vai sempre dizeque algum morreu para acha que ainda esta a espera
                if (i == data->n_philos - 1)
                        i = -1;
        }
        return (NULL);
}

bool    check_diff(long diff, t_data *data, t_philo *philo)
{
        if (get_bool(&philo->mtx_full, &philo->full))
                return (false);
        if (diff > data->time_to_die)
        {
                set_bool(&philo->mtx_die, &philo->die, true);
                set_bool(&data->mtx_end, &data->end_status, true);
                print_action(DIE, get_time() - data->start_time, &data->mtx_print, philo);
                return (true);
        }
        return (false);
}
