/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:32:44 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/20 23:39:33 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	take_dongle(t_data *data, t_dongle *dongle, t_coder *coder)
{
	t_request	req;

	req.coder_id = coder->id;
	pthread_mutex_lock(&dongle->mutex);
	heap_push(&dongle->heap, req);
	if (wait_for_turn(data, dongle, coder->id))
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (0);
	}
	heap_pop(&dongle->heap);
	dongle->in_use = 1;
	pthread_mutex_unlock(&dongle->mutex);
	return (1);
}

static int	take_two_dongles(t_data *data, t_coder *coder)
{
	if (data->scheduler == EDF)
	{
		if (!take_edf_pair(data, coder))
			return (0);
		log_state(data, coder->id, "has taken a dongle");
		log_state(data, coder->id, "has taken a dongle");
		return (1);
	}
	if (!take_dongle(data, coder->first_dongle, coder))
		return (0);
	if (!take_dongle(data, coder->second_dongle, coder))
	{
		dongle_release(coder->first_dongle, 0);
		return (0);
	}
	log_state(data, coder->id, "has taken a dongle");
	log_state(data, coder->id, "has taken a dongle");
	return (1);
}

static void	do_task(t_data *data, t_coder *coder)
{
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile_start = now();
	log_state(data, coder->id, "is compiling");
	sleep_ms(data, coder->time_to_compile);
	pthread_mutex_unlock(&coder->mutex);
	dongle_release(coder->first_dongle, 1);
	dongle_release(coder->second_dongle, 1);
	pthread_mutex_lock(&data->scheduling_mutex);
	pthread_cond_broadcast(&data->scheduling_cond);
	pthread_mutex_unlock(&data->scheduling_mutex);
	log_state(data, coder->id, "is debugging");
	sleep_ms(data, coder->time_to_debug);
	log_state(data, coder->id, "is refactoring");
	sleep_ms(data, coder->time_to_refactor);
}

void	*coder_thread(void *arg)
{
	t_data_and_coder	*dc;
	t_data				*data;
	t_coder				*coder;
	int					done;

	dc = (t_data_and_coder *)arg;
	data = dc->data;
	coder = dc->coder;
	if ((coder->id - 1) % 2)
		usleep(100);
	while (!is_stopped(data))
	{
		if (!take_two_dongles(data, coder))
			break ;
		do_task(data, coder);
		pthread_mutex_lock(&coder->mutex);
		coder->compile_count++;
		done = (coder->compile_count >= coder->compiles_required);
		pthread_mutex_unlock(&coder->mutex);
		if (done)
			break ;
	}
	free(dc);
	return (NULL);
}
