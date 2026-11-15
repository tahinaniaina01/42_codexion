/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:18:56 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 16:21:49 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_stop(t_data *data)
{
	int	stoped;

	pthread_mutex_lock(&data->log_mutex);
	stoped = data->stop;
	pthread_mutex_unlock(&data->log_mutex);
	return (stoped);
}
