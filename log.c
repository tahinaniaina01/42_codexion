/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:18:56 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 17:03:32 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_stop(t_data *data)
{
	int	stoped;

	pthread_mutex_lock(&data->log_mutex);
	stoped = data->stop;
	pthread_mutex_unlock(&data->log_mutex);
	return (stoped);
}

void	log_state(t_data *data, int id, char *message)
{
	pthread_mutex_lock(&data->log_mutex);
	if (!data->stop)
		printf("%ld %d %s\n", now_ms() - data->start_time, id, message);
	pthread_mutex_unlock(&data->log_mutex);
}

void	stop_codexion(t_data *data)
{
	pthread_mutex_lock(&data->log_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->log_mutex);
}
