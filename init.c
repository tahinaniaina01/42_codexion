/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 11:59:11 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 20:32:05 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	asigne_dongles(t_data *data, int index)
{
	int	left;
	int	right;

	left = index;
	right = (index + 1) % data->n_coders;
	if (left > right)
	{
		data->coders[index].first_dongle = &data->dongles[left];
		data->coders[index].second_dongle = &data->dongles[right];
	}
	else
	{
		data->coders[index].first_dongle = &data->dongles[right];
		data->coders[index].second_dongle = &data->dongles[left];
	}
}

int	init_coders(t_data *data, t_input *inputs)
{
	int	i;

	data->coders = (t_coder *)malloc(sizeof(t_coder) * inputs->n_coders);
	if (!data->coders)
		return (2);
	i = 0;
	while (i < inputs->n_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].burnout_time = inputs->time_to_burnout;
		data->coders[i].time_to_compile = inputs->time_to_compile;
		data->coders[i].time_to_debug = inputs->time_to_debug;
		data->coders[i].time_to_refactor = inputs->time_to_refactor;
		data->coders[i].last_compile_start = 0;
		data->coders[i].compile_count = 0;
		data->coders[i].compiles_required = inputs->number_of_compiles_required;
		asigne_dongles(data, i);
		if (pthread_mutex_init(&data->coders[i].mutex, NULL) != 0)
		{
			return (3);
		}
		i++;
	}
	return (0);
}

int	init_dongles(t_data *data, t_input *inputs)
{
	int	i;

	data->dongles = (t_dongle *)malloc(sizeof(t_dongle) * inputs->n_coders);
	if (!data->dongles)
		return (2);
	i = 0;
	while (i < data->n_coders)
	{
		if (pthread_mutex_init(&data->dongles[i].mutex, NULL) != 0)
			return (3);
		if (pthread_cond_init(&data->dongles[i].cond, NULL) != 0)
		{
			pthread_mutex_destroy(&data->dongles[i].mutex);
			return (3);
		}
		data->dongles[i].heap = NULL;
		data->dongles[i].in_use = 0;
		data->dongles[i].available_at = 0;
		data->dongles[i].cooldown = inputs->dongle_cooldown;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, t_input *inputs)
{
	int	r;

	data->stop = 0;
	data->n_coders = inputs->n_coders;
	data->scheduler = inputs->scheduler;
	if (pthread_mutex_init(&data->log_mutex, NULL) != 0)
		return (3);
	r = init_dongles(data, inputs);
	if (r)
	{
		pthread_mutex_destroy(&data->log_mutex);
		return (r);
	}
	r = init_coders(data, inputs);
	if (r)
	{
		destroy_dongles(data->dongles, data->n_coders);
		pthread_mutex_destroy(&data->log_mutex);
		return (r);
	}
	return (0);
}
