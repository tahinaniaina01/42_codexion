/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:18:56 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/22 14:31:49 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	is_stopped(t_data *data)
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
		printf("%ld %d %s\n", now() - data->start_time, id, message);
	pthread_mutex_unlock(&data->log_mutex);
}

void	stop_codexion(t_data *data)
{
	pthread_mutex_lock(&data->log_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->log_mutex);
}

static void	wake_all_dongles(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_coders)
	{
		pthread_mutex_lock(&data->dongles[i].mutex);
		pthread_cond_broadcast(&data->dongles[i].cond);
		pthread_mutex_unlock(&data->dongles[i].mutex);
		i++;
	}
	pthread_mutex_lock(&data->scheduling_mutex);
	pthread_cond_broadcast(&data->scheduling_cond);
	pthread_mutex_unlock(&data->scheduling_mutex);
}

void	declare_burnout(t_data *data, int id)
{
	pthread_mutex_lock(&data->log_mutex);
	if (!data->stop)
	{
		data->stop = 1;
		printf("%ld %d burned out\n", now() - data->start_time, id);
	}
	pthread_mutex_unlock(&data->log_mutex);
	wake_all_dongles(data);
}
