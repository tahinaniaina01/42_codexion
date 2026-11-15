/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:36:53 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 16:32:04 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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

int	codexion(t_data *data)
{
	set_start_time(data);
}
