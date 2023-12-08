/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_collisions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:00:27 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/08 14:00:27 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

t_list	**create_overflow_buckets(t_hash_table *table)
{
    t_list	**buckets;
	size_t	i;

	buckets = (t_list**) ft_calloc(table->size, sizeof(t_list*));
	if (buckets == NULL)
		return (NULL);
	i = 0;
    while (i < table->size)
        buckets[i++] = NULL;
    return (buckets);
}

void	handle_collision(t_hash_table *table, unsigned long hash, t_ht_item *item)
{
	t_list*	head;
	
	head = table->overflow_buckets[hash];
    if (head == NULL)
    {
        head = ft_lstnew(item);
        table->overflow_buckets[hash] = head;
    }
    else 
        ft_lstadd_front(&head, ft_lstnew(item));
}

void	free_overflow_buckets(t_hash_table *table)
{
    t_list	**buckets;
	size_t	i;
	
	buckets = table->overflow_buckets;
	i = 0;
    while (i < table->size)
	{
        ft_lstclear(&buckets[i], &free_item);
		i++;
	}
    free(buckets);
}