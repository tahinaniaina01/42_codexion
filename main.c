/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:37:46 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 15:56:11 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// static void	print_inputs(t_input *inputs)
// {
// 	printf("n coders: %d\n", inputs->n_coders);
// 	printf("time_to_burnout: %d\n", inputs->time_to_burnout);
// 	printf("time_to_compile: %d\n", inputs->time_to_compile);
// 	printf("time_to_debug: %d\n", inputs->time_to_debug);
// 	printf("time_to_refactor: %d\n", inputs->time_to_refactor);
// 	printf("number_of_compiles_required: %d\n",
// 		inputs->number_of_compiles_required);
// 	printf("dongle_cooldown: %d\n", inputs->dongle_cooldown);
// 	printf("scheduler: %s\n", inputs->scheduler ? "edf" : "fifo");
// }

int	main(void)
{
	t_heap		*heap;
	t_request	a;

	heap = NULL;
	// t_input	*inputs;
	// t_data	data;
	// inputs = parse(ac, av);
	// if (inputs == NULL)
	// {
	// 	fprintf(stderr,
	// 			"Invalid inputs\nusage: ./codexion <n_coders: number> "
	// 			"<time_to_burnout: number> <time_to_compile: number> <time_to_debug: number> "
	// 			"<time_to_refactor: number> <number_of_compiles_required: number> "
	// 			"<dongle_cooldown: number> <scheduler: 'fifo' | 'edf'>");
	// 	return (1);
	// }
	// print_inputs(inputs);
	// init_data(&data, inputs);
	// free(inputs);
	for (int i = 0; i < 10; i += 2)
	{
		a.coder_id = i;
		a.preority = i;
		a.sheduler = EDF;
		printf("push %d\n", a.preority);
		heap_push(&heap, a);
	}
	a.coder_id = 3;
	a.preority = 10;
	a.sheduler = EDF;
	heap_push(&heap, a);
	for (t_heap *i = heap; i != NULL; i = i->next)
	{
		printf("%d ", i->value.preority);
	}
	clear_heap(&heap);
	return (0);
}
