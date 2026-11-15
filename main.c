/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:37:46 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 21:30:35 by trakotos         ###   ########.fr       */
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
		fprintf(stderr, "Invalid inputs\n");
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
