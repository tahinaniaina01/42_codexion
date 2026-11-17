/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:36:53 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/17 13:41:55 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	join_coder(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_coders)
	{
		pthread_join(data->coders[i].thread, NULL);
		i++;
	}
}

static void	set_start_time(t_data *data)
{
	int	i;

	data->start_time = now();
	i = 0;
	while (i < data->n_coders)
	{
		data->coders[i].last_compile_start = data->start_time;
		i++;
	}
}

int	start_coders(t_data *data)
{
	int					i;
	t_data_and_coder	*dc;

	i = 0;
	while (i < data->n_coders)
	{
		dc = (t_data_and_coder *)malloc(sizeof(t_data_and_coder));
		if (dc == NULL)
		{
			stop_codexion(data);
			join_coder(data);
			return (2);
		}
		dc->data = data;
		dc->coder = &data->coders[i];
		if (pthread_create(&data->coders[i].thread, NULL, coder_thread,
				dc) != 0)
		{
			stop_codexion(data);
			join_coder(data);
			return (2);
		}
		i++;
	}
	return (0);
}

int	codexion(t_data *data)
{
	set_start_time(data);
	if (start_coders(data) != 0)
		return (2);
	if (pthread_create(&data->monitor, NULL, monitor_thread, data) != 0)
	{
		stop_codexion(data);
		join_coder(data);
		return (2);
	}
	pthread_join(data->monitor, NULL);
	join_coder(data);
	return (0);
}
