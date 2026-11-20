/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trakotos <trakotos@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 13:18:03 by trakotos          #+#    #+#             */
/*   Updated: 2026/11/21 00:47:52 by trakotos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	heap_push(t_heap **heap, t_request val)
{
	t_heap	*new;
	t_heap	*tmp;

	new = (t_heap *)malloc(sizeof(t_heap));
	if (new == NULL)
		return ;
	new->value = val;
	new->next = NULL;
	if (*heap == NULL)
	{
		*heap = new;
		return ;
	}
	tmp = *heap;
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
