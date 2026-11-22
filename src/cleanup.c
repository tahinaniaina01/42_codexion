/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 13:04:58 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/22 14:31:49 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/codexion.h"

void	destroy_dongles(t_dongle *dongles, int n_dongles)
{
	int	i;

	i = 0;
	while (i < n_dongles)
	{
		pthread_mutex_destroy(&dongles[i].mutex);
		pthread_cond_destroy(&dongles[i].cond);
		clear_heap(&dongles[i].heap);
		i++;
	}
	free(dongles);
}

void	destroy_coders(t_coder *coders, int n_coders)
{
	int	i;

	i = 0;
	while (i < n_coders)
	{
		pthread_mutex_destroy(&coders[i].mutex);
		i++;
	}
	free(coders);
}

void	cleanup_data(t_data *data)
{
	destroy_dongles(data->dongles, data->n_coders);
	destroy_coders(data->coders, data->n_coders);
	pthread_cond_destroy(&data->scheduling_cond);
	pthread_mutex_destroy(&data->scheduling_mutex);
	pthread_mutex_destroy(&data->log_mutex);
}
