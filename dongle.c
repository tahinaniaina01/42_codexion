/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 18:33:47 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 19:51:38 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_myturn(t_dongle *dongle, int coder_id)
{
	if (dongle->heap == NULL)
		return (0);
	return (dongle->heap->value.coder_id == coder_id && !dongle->in_use);
}

static int	can_take(t_dongle *dongle, int coder_id)
{
	return (is_myturn(dongle, coder_id) && now() >= dongle->available_at);
}

int	wait_for_turn(t_data *data, t_dongle *dongle, int coder_id)
{
	struct timespec	limit;

	while (!is_stopped(data))
	{
		if (can_take(dongle, coder_id))
			return (0);
		if (is_myturn(dongle, coder_id))
		{
			ms_to_timespec(dongle->available_at, &limit);
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &limit);
		}
		else
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
	return (1);
}

void	dongle_release(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->in_use = 0;
	dongle->available_at = now() + dongle->cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
