/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:37:46 by trakotos          #+#    #+#             */
/*   Updated: 2026/09/26 16:35:08 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/codexion.h"
#include "headers/parser.h"

static	print_inputs(t_input *inputs)
{
	printf("n coders: %d", inputs->n_coders);
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

	inputs = parse(ac, av);
	if (inputs == NULL)
	{
		fprintf(stderr,
				"Invalid inputs\nusage: ./codexion <n_coders> "
				"<time_to_burnout> <time_to_compile> <time_to_debug> "
				"<time_to_refactor> <number_of_compiles_required> "
				"<dongle_cooldown> <scheduler>");
		return (1);
	}
	print_inputs(inputs);
	return (0);
}
