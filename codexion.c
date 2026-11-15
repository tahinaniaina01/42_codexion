/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:36:53 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 17:19:10 by trakotos         ###   ########.fr       */
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

static int	start_coders(t_data *data)
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
			return (1);
		}
		dc->data = data;
		dc->coder = &data->coders[i];
		if (pthread_create(&data->coders[i].thread, NULL, (void *)coder_routing,
				dc) != 0)
		{
			stop_codexion(data);
			join_coder(data);
			return (1);
		}
		i++;
	}
}

int	codexion(t_data *data)
{
	set_start_time(data);
	if (start_coders(data) != 0)
		return (1);
}
