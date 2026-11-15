/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:37:46 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 18:09:01 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int ac, char **av)
{
	t_input	*inputs;
	t_data	data;
	int		r;

	inputs = parse(ac, av);
	if (inputs == NULL)
	{
		fprintf(stderr,
				"Invalid inputs\nusage: ./codexion <n_coders: number> "
				"<time_to_burnout: number> <time_to_compile: number> <time_to_debug: number> "
				"<time_to_refactor: number> <number_of_compiles_required: number> "
				"<dongle_cooldown: number> <scheduler: 'fifo' | 'edf'>");
		return (1);
	}
	r = init_data(&data, inputs);
	if (r)
	{
		free(inputs);
		return (r);
	}
	if (codexion(&data))
		fprintf(stderr, "Error: could not create the threads\n");
	free(inputs);
	cleanup_data(&data);
	return (0);
}
