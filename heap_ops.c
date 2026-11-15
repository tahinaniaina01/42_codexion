/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 13:18:03 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/15 15:10:09 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_push(t_heap **heap, t_request *val)
{
	t_heap	*new;
	t_heap	*tmp;
	t_heap	*next;

	new = (t_heap *)malloc(sizeof(t_heap));
	if (*heap == NULL)
	{
		*heap == new;
		return ;
	}
	tmp = *heap;
	if (val->sheduler == EDF)
	{
		while (tmp->next != NULL)
		{
			if (tmp->next->value.preority > new->value.preority)
			{
				next = tmp->next;
				tmp->next = new;
				new->next = next;
			}
			tmp = tmp->next;
		}
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
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
