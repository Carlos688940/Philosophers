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

bool    check_diff(long diff, t_data *data);

void    *monitoring(void *info)
{
        int     i;
        t_data *data;

        data = (t_data *)info;
        i = -1;
        wait_init(data);
        while (!get_bool(&data->mtx_end, &data->end_status))
        {
                ++i;
                if (get_bool(&data->philos[i].mtx_die, &data->philos[i].die))
                {
                        printf("entrei\n");
                        set_bool(&data->mtx_end, &data->end_status, true);
                        print_action(DIE, get_time() - data->start_time, &data->mtx_print, &data->philos[i]);
                        break;
                }

                if (i == data->n_philos - 1)
                        i = -1;
        }
        return (NULL);
}

bool    check_diff(long diff, t_data *data)
{
        if (diff > data->time_to_die)
        {
                set_bool(&data->mtx_end, &data->end_status, true);
                return (true);
        }
        return (false);
}
