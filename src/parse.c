/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 15:44:03 by trakotos          #+#    #+#             */
/*   Updated: 2026/09/26 16:45:43 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parser.h"

static int	is_integer(char *str)
{
	size_t	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac - 1)
	{
		if (!is_integer(av[i]))
			return (0);
		i++;
	}
	if (strcmp(av[i], "fifo") && strcmp(av[i], "edf"))
		return (0);
	return (1);
}

t_input	*parse(int ac, char **av)
{
	t_input	*inputs;

	inputs = (t_input *)malloc(sizeof(t_input));
	if (ac != 9 || !is_valid(ac, av))
		return (NULL);
	inputs->n_coders = atoi(av[1]);
	inputs->time_to_burnout = atoi(av[2]);
	inputs->time_to_compile = atoi(av[3]);
	inputs->time_to_debug = atoi(av[4]);
	inputs->time_to_refactor = atoi(av[5]);
	inputs->number_of_compiles_required = atoi(av[6]);
	inputs->dongle_cooldown = atoi(av[7]);
	if (!strcmp(av[8], "fifo"))
		inputs->scheduler = FIFO;
	else
		inputs->scheduler = EDF;
	return (inputs);
}
