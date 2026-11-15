/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 17:19:26 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 17:34:18 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	all_coder_done(t_data *data)
{
	int	i;
	int	done;

	i = 0;
	while (i < data->n_coders)
	{
		pthread_mutex_lock(&data->coders[i].mutex);
		done = (data->coders[i].compile_count >= data->coders[i].compiles_required);
		pthread_mutex_unlock(&data->coders[i].mutex);
		if (!done)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_thread(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!is_stopped(data))
	{
		if (all_coder_done(data))
			stop_codexion(data);
		usleep(1000);
	}
	return (NULL);
}
