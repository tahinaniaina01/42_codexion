/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:32:44 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 17:27:32 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_thread(void *arg)
{
	t_data_and_coder	*dc;
	t_data				*data;
	t_coder				*coder;
	int					done;

	dc = (t_data_and_coder *)arg;
	data = dc->data;
	coder = dc->coder;
	free(dc);
	while (!is_stopped(data))
	{
		log_state(data, coder->id, "is compiling");
		sleep_ms(data, coder->time_to_compile);
		log_state(data, coder->id, "is debugging");
		sleep_ms(data, coder->time_to_debug);
		log_state(data, coder->id, "is refactoring");
		sleep_ms(data, coder->time_to_refactor);
		pthread_mutex_lock(&coder->mutex);
		coder->compile_count++;
		done = (coder->compile_count >= coder->compiles_required);
		pthread_mutex_unlock(&coder->mutex);
		if (done)
			break ;
	}
	return (NULL);
}
