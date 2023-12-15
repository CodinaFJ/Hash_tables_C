/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:25:28 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/08 12:25:28 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

unsigned long	hash_from_str(char *str)
{
    size_t			i;
	unsigned long	hash;

	i = 0;
	hash = 0;
	while (str[i])
	{
		hash += str[i];
		hash *= 33;
		hash = hash;
		i++;
	}
    return (hash % HT_CAPACITY);
}


void	ft_delete_in_overflow_bucket(t_list **head, char *key, t_hash_table *table, unsigned long hash)
{
	t_list	*curr;
	t_list	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(((t_ht_item *)curr->content)->key, key) == 0)
		{
			if (prev == NULL)
			{
				// First element of the chain.
				table->overflow_buckets[hash] = curr->next;
				curr->next = NULL;
				ft_lstclear(&curr, &free_item);
				return;
			}
			else
			{
				// Somewhere in the chain.
				prev->next = curr->next;
				curr->next = NULL;
				ft_lstclear(&curr, &free_item);
				return;
			}
		}
		curr = curr->next;
		prev = curr;
	}
}

void	ht_delete(t_hash_table *table, char *key)
{
	unsigned long	hash;
	t_ht_item		*item;
	t_list			*head;
	t_list			*node;

	hash = hash_from_str(key);
	item = table->items[hash];
	head = table->overflow_buckets[hash];
	node = NULL;
	if (item == NULL)
		return ;
	if (ft_strcmp(item->key, key) == 0)
	{
		if (head == NULL)
		{
			table->items[hash] = NULL;
			free_item(item);
			table->count--;
			return ;
		}
		else
		{
			free_item(item);
			node = head;
			head = head->next;
			node->next = NULL;
			table->items[hash] = create_item(((t_ht_item *) node->content)->key,  ((t_ht_item *) node->content)->value);
			ft_lstclear(&node, &free_item);
			table->overflow_buckets[hash] = head;
			return ;
		}
	}
	else if (head != NULL)
		ft_delete_in_overflow_bucket(&head, key, table, hash);
}