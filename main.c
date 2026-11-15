/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:37:46 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 17:41:21 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	print_inputs(t_input *inputs)
{
	printf("n coders: %d\n", inputs->n_coders);
	printf("time_to_burnout: %d\n", inputs->time_to_burnout);
	printf("time_to_compile: %d\n", inputs->time_to_compile);
	printf("time_to_debug: %d\n", inputs->time_to_debug);
	printf("time_to_refactor: %d\n", inputs->time_to_refactor);
	printf("number_of_compiles_required: %d\n",
		inputs->number_of_compiles_required);
	printf("dongle_cooldown: %d\n", inputs->dongle_cooldown);
	printf("scheduler: %s\n", inputs->scheduler ? "edf" : "fifo");
}

int	main(int ac, char **av)
{
	t_input	*inputs;
	t_data	data;

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
	print_inputs(inputs);
	if (init_data(&data, inputs))
		return (1);
	if (codexion(&data))
		fprintf(stderr, "Error: could not create the threads\n");
	free(inputs);
	cleanup_data(&data);
	return (0);
}
