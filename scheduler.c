/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 23:55:00 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/20 23:55:00 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_priority	get_priority(t_coder *coder)
{
	t_priority	p;

	pthread_mutex_lock(&coder->mutex);
	p.deadline = coder->last_compile_start + coder->burnout_time;
	p.wait_since = coder->wait_since;
	p.count = coder->compile_count;
	p.id = coder->id;
	pthread_mutex_unlock(&coder->mutex);
	return (p);
}

static int	other_is_prior(t_coder *coder, t_coder *other)
{
	t_priority	own;
	t_priority	p;

	own = get_priority(coder);
	p = get_priority(other);
	if (p.count >= other->compiles_required)
		return (0);
	if (p.deadline != own.deadline)
		return (p.deadline < own.deadline);
	if (p.count != own.count)
		return (p.count < own.count);
	if (p.wait_since != own.wait_since)
		return (p.wait_since < own.wait_since);
	return (p.id < own.id);
}

static int	is_edf_priority(t_data *data, t_coder *coder)
{
	int	i;

	i = -1;
	while (++i < data->n_coders)
	{
		if (other_is_prior(coder, &data->coders[i]))
			return (0);
	}
	return (1);
}

static int	pair_available(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;
	long		now_ms;

	first = coder->first_dongle;
	second = coder->second_dongle;
	now_ms = now();
	pthread_mutex_lock(&first->mutex);
	if (second != first)
		pthread_mutex_lock(&second->mutex);
	if (first->in_use || second->in_use
		|| now_ms < first->available_at
		|| now_ms < second->available_at)
	{
		if (second != first)
			pthread_mutex_unlock(&second->mutex);
		pthread_mutex_unlock(&first->mutex);
		return (0);
	}
	first->in_use = 1;
	second->in_use = 1;
	if (second != first)
		pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	return (1);
}

int	take_edf_pair(t_data *data, t_coder *coder)
{
	struct timespec	limit;

	pthread_mutex_lock(&data->scheduling_mutex);
	while (!is_stopped(data))
	{
		pthread_mutex_lock(&coder->mutex);
		if (coder->wait_since == 0)
			coder->wait_since = now();
		pthread_mutex_unlock(&coder->mutex);
		if (is_edf_priority(data, coder) && pair_available(coder))
		{
			pthread_mutex_lock(&coder->mutex);
			coder->wait_since = 0;
			pthread_mutex_unlock(&coder->mutex);
			pthread_mutex_unlock(&data->scheduling_mutex);
			return (1);
		}
		ms_to_timespec(now() + 1, &limit);
		pthread_cond_timedwait(&data->scheduling_cond,
			&data->scheduling_mutex, &limit);
	}
	pthread_mutex_unlock(&data->scheduling_mutex);
	return (0);
}
