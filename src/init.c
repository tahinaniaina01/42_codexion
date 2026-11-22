/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 11:59:11 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/22 14:31:49 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

int	init_scheduling(t_data *data);
int	init_dongles(t_data *data, t_input *inputs);
int	init_coders(t_data *data, t_input *inputs);

static void	cleanup_init(t_data *data)
{
	pthread_cond_destroy(&data->scheduling_cond);
	pthread_mutex_destroy(&data->scheduling_mutex);
	pthread_mutex_destroy(&data->log_mutex);
}

static int	init_resources(t_data *data, t_input *inputs)
{
	int	r;

	r = init_scheduling(data);
	if (r)
		return (r);
	r = init_dongles(data, inputs);
	if (r)
		return (r);
	r = init_coders(data, inputs);
	if (r)
		destroy_dongles(data->dongles, data->n_coders);
	return (r);
}

int	init_data(t_data *data, t_input *inputs)
{
	int	r;

	data->stop = 0;
	data->n_coders = inputs->n_coders;
	data->scheduler = inputs->scheduler;
	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
		return (3);
	r = init_resources(data, inputs);
	if (r)
	{
		cleanup_init(data);
		return (r);
	}
	return (0);
}
