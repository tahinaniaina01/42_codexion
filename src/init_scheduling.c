/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scheduling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 23:59:00 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/22 14:31:49 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	init_scheduling(t_data *data)
{
	if (pthread_mutex_init(&data->scheduling_mutex, NULL) != 0)
		return (3);
	if (pthread_cond_init(&data->scheduling_cond, NULL) != 0)
	{
		pthread_mutex_destroy(&data->scheduling_mutex);
		return (3);
	}
	return (0);
}
