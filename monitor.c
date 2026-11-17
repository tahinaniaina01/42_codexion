/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 17:19:26 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/17 13:42:10 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	has_burned_out(t_coder *coder)
{
	long	elapsed;
	int		done;

	pthread_mutex_lock(&coder->mutex);
	done = (coder->compile_count >= coder->compiles_required);
	elapsed = now() - coder->last_compile_start;
	pthread_mutex_unlock(&coder->mutex);
	if (done)
		return (0);
	return (elapsed > coder->burnout_time);
}

static int	check_burnouts(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_coders)
	{
		if (has_burned_out(&data->coders[i]))
		{
			declare_burnout(data, data->coders[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_coder_done(t_data *data)
{
	int	i;
	int	d;

	i = 0;
	while (i < data->n_coders)
	{
		pthread_mutex_lock(&data->coders[i].mutex);
		d = data->coders[i].compile_count >= data->coders[i].compiles_required;
		pthread_mutex_unlock(&data->coders[i].mutex);
		if (!d)
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
		if (check_burnouts(data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
