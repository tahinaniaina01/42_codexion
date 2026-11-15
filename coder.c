/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 16:32:44 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 16:59:07 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_routing(void *arg)
{
	t_data_and_coder	*dc;

	dc = (t_data_and_coder *)arg;
	while (!is_stop(dc->data))
	{
		log_state(dc->data, dc->coder->id, "is compiling");
		sleep_ms(dc->data, dc->coder->time_to_compile);
		dc->coder->compile_count++;
		log_state(dc->data, dc->coder->id, "is debugging");
		sleep_ms(dc->data, dc->coder->time_to_debug);
		log_state(dc->data, dc->coder->id, "is refactoring");
		sleep_ms(dc->data, dc->coder->time_to_refactor);
	}
	return (NULL);
}
