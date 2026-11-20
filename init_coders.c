/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/20 23:59:00 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/21 00:55:09 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	assign_dongles(t_data *data, int index)
{
	int	left;
	int	right;

	left = index;
	right = (index + 1) % data->n_coders;
	if (index % 2)
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

static int	init_one_coder(t_coder *coder, t_input *inputs, int index)
{
	coder->id = index + 1;
	coder->burnout_time = inputs->time_to_burnout;
	coder->time_to_compile = inputs->time_to_compile;
	coder->time_to_debug = inputs->time_to_debug;
	coder->time_to_refactor = inputs->time_to_refactor;
	coder->last_compile_start = 0;
	coder->wait_since = 0;
	coder->compile_count = 0;
	coder->compiles_required = inputs->number_of_compiles_required;
	if (pthread_mutex_init(&coder->mutex, NULL) != 0)
		return (3);
	return (0);
}

int	init_coders(t_data *data, t_input *inputs)
{
	int	i;
	int	r;

	data->coders = malloc(sizeof(t_coder) * inputs->n_coders);
	if (!data->coders)
		return (2);
	i = -1;
	while (++i < inputs->n_coders)
	{
		r = init_one_coder(&data->coders[i], inputs, i);
		if (r)
			return (r);
		assign_dongles(data, i);
	}
	return (0);
}
