/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 14:37:03 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 21:08:15 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
#define CODEXION_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

typedef enum e_sheduler
{
	FIFO,
	EDF
} t_scheduler;

typedef struct s_input
{
	int n_coders;
	int time_to_burnout;
	int time_to_compile;
	int time_to_debug;
	int time_to_refactor;
	int number_of_compiles_required;
	int dongle_cooldown;
	t_scheduler scheduler;
} t_input;

typedef struct s_request
{
	int coder_id;
	long preority;
	t_scheduler sheduler;
} t_request;

typedef struct s_heap
{
	t_request value;
	struct s_heap *next;
} t_heap;

typedef struct s_dongle
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int in_use;
	int available_at;
	t_heap *heap;
	int cooldown;
} t_dongle;

typedef struct s_coder
{
	int id;
	pthread_mutex_t mutex;
	pthread_t thread;
	t_dongle *first_dongle;
	t_dongle *second_dongle;
	long burnout_time;
	long time_to_compile;
	long time_to_debug;
	long time_to_refactor;
	long last_compile_start;
	int compile_count;
	int compiles_required;
	int nb_dongles;
} t_coder;

typedef struct s_data
{
	int n_coders;
	t_coder *coders;
	t_dongle *dongles;
	pthread_mutex_t log_mutex;
	pthread_t monitor;
	int stop;
	long start_time;
	t_scheduler scheduler;
} t_data;

typedef struct s_data_and_coder
{
	t_data *data;
	t_coder *coder;
} t_data_and_coder;

t_input *parse(int ac, char **av);
int init_data(t_data *data, t_input *inputs);
void destroy_dongles(t_dongle *dongles, int n_dongles);
void destroy_coders(t_coder *coders, int n_coders);
void cleanup_data(t_data *data);
void heap_push(t_heap **heap, t_request val);
void heap_pop(t_heap **heap);
void clear_heap(t_heap **heap);
long now(void);
void sleep_ms(t_data *data, long duration);
void ms_to_timespec(long ms, struct timespec *ts);
int is_stopped(t_data *data);
int codexion(t_data *data);
void *coder_thread(void *arg);
void log_state(t_data *data, int id, char *message);
void stop_codexion(t_data *data);
void *monitor_thread(void *arg);
int wait_for_turn(t_data *data, t_dongle *dongle, int coder_id);
void dongle_release(t_dongle *dongle, int with_cooldon);
void declare_burnout(t_data *data, int id);

#endif
