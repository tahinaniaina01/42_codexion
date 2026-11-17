/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 13:18:03 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/17 13:42:02 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	sort_push(t_heap **heap, t_heap *new)
{
	t_heap	*tmp;
	t_heap	*next;

	tmp = *heap;
	if (tmp->value.preority > new->value.preority)
	{
		new->next = tmp;
		*heap = new;
		return ;
	}
	while (tmp->next != NULL)
	{
		if (tmp->next->value.preority > new->value.preority)
		{
			next = tmp->next;
			tmp->next = new;
			new->next = next;
			return ;
		}
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	heap_push(t_heap **heap, t_request val)
{
	t_heap	*new;
	t_heap	*tmp;

	new = (t_heap *)malloc(sizeof(t_heap));
	new->value = val;
	new->next = NULL;
	if (*heap == NULL)
	{
		*heap = new;
		return ;
	}
	tmp = *heap;
	if (val.sheduler == EDF)
	{
		sort_push(heap, new);
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	heap_pop(t_heap **heap)
{
	t_heap	*tmp;

	if (heap == NULL || *heap == NULL)
		return ;
	tmp = *heap;
	*heap = (*heap)->next;
	free(tmp);
}

void	clear_heap(t_heap **heap)
{
	t_heap	*cur;

	while (*heap != NULL)
	{
		cur = *heap;
		*heap = (*heap)->next;
		free(cur);
	}
}
