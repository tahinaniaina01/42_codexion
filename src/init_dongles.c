/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 23:59:00 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/22 14:31:49 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

static int	init_one_dongle(t_dongle *dongle, t_input *inputs)
{
	dongle->heap = NULL;
	dongle->in_use = 0;
	dongle->available_at = now();
	dongle->cooldown = inputs->dongle_cooldown;
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
		return (3);
	if (pthread_cond_init(&dongle->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (3);
	}
	return (0);
}

int	init_dongles(t_data *data, t_input *inputs)
{
	int	i;
	int	r;

	data->dongles = malloc(sizeof(t_dongle) * inputs->n_coders);
	if (!data->dongles)
		return (2);
	i = -1;
	while (++i < data->n_coders)
	{
		r = init_one_dongle(&data->dongles[i], inputs);
		if (r)
			return (r);
	}
	return (0);
}
