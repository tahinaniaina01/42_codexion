/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 15:46:43 by trakotos          #+#    #+#             */
/*   Updated: 2026/09/26 16:29:04 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <string.h>

typedef enum e_sheduler
{
	FIFO,
	EDF
}				t_scheduler;

typedef struct s_input
{
	int			n_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	t_scheduler	scheduler;
}				t_input;

t_input			*parse(int ac, char **av);

#endif