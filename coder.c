/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:32:44 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 19:07:11 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long	get_preority(t_coder *coder)
{
	long	priority;

	pthread_mutex_lock(&coder->mutex);
	priority = coder->last_compile_start + coder->burnout_time;
	pthread_mutex_unlock(&coder->mutex);
	return (priority);
}

static int	take_dongle(t_data *data, t_dongle *dongle, t_coder *coder)
{
	t_request	req;

	req.coder_id = coder->id;
	req.sheduler = data->scheduler;
	req.preority = get_preority(coder);
	pthread_mutex_lock(&dongle->mutex);
	heap_push(&dongle->queue, req);
	pthread_mutex_unlock(&dongle->mutex);
	return (1);
}

static int	take_two_dongles(t_data *data, t_coder *coder)
{
	if (!take_dongle(data, coder->first_dongle, coder))
		return (0);
	if (!take_dongle(data, coder->second_dongle, coder))
		return (0);
	return (1);
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
	free(dc);
	while (!is_stopped(data))
	{
		if (!take_two_dongles(data, coder))
			break ;
		log_state(data, coder->id, "is compiling");
		sleep_ms(data, coder->time_to_compile);
		log_state(data, coder->id, "is debugging");
		sleep_ms(data, coder->time_to_debug);
		log_state(data, coder->id, "is refactoring");
		sleep_ms(data, coder->time_to_refactor);
		pthread_mutex_lock(&coder->mutex);
		coder->compile_count++;
		done = (coder->compile_count >= coder->compiles_required);
		pthread_mutex_unlock(&coder->mutex);
		if (done)
			break ;
	}
	return (NULL);
}
