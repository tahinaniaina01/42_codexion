/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 11:59:11 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 14:26:56 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	init_coders(t_data *data, t_input *inputs)
{
	int	i;

	data->coders = (t_coder *)malloc(sizeof(t_coder) * inputs->n_coders);
	if (!data->coders)
		return (1);
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
		data->coders[i].first_dongle = &data->dongles[i];
		data->coders[i].second_dongle = &data->dongles[(i + 1)
			% data->n_coders];
		if (pthread_mutex_init(&data->coders[i].mutex, NULL) != 0)
		{
			return (1);
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
		return (1);
	i = 0;
	while (i < data->n_coders)
	{
		if (pthread_mutex_init(&data->dongles[i].mutex, NULL) != 0)
			return (1);
		if (pthread_cond_init(&data->dongles[i].cond, NULL) != 0)
		{
			pthread_mutex_destroy(&data->dongles[i].mutex);
			return (1);
		}
		data->dongles[i].queue = NULL;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, t_input *inputs)
{
	data->stop = 0;
	data->n_coders = inputs->n_coders;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (!init_dongles(data, inputs))
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (1);
	}
	if (!init_coders(data, inputs))
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (1);
	}
	return (0);
}
