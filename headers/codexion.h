/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:37:03 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 11:55:11 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum e_sheduler
{
	FIFO,
	EDF
}					t_scheduler;

typedef struct s_input
{
	int				n_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	t_scheduler		scheduler;
}					t_input;

typedef struct s_request
{
	int				coder_id;
	int				preority;
}					t_request;

typedef struct s_heap
{
	t_request		value;
	struct s_heap	*next;
}					t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				in_use;
	int				available_at;
	t_heap			*queue;
	int				cooldown;
}					t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_mutex_t	mutex;
	pthread_t		thread;
	t_dongle		*right_dongle;
	t_dongle		*left_dongle;
	long			time_to_burnout;
	long			time_to_compile;
	long			time_to_debug;
	long			time_to_refactor;
	long			last_compile_start;
	int				compile_count;
}					t_coder;

typedef struct s_data
{
	int				n_coders;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	print_mutex;
	pthread_t		monitor;
	int				stop;
}					t_data;

t_input				*parse(int ac, char **av);

#endif
