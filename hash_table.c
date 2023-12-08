/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:38:36 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/08 11:38:36 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

t_ht_item	*create_item(char *key, char *value)
{
	t_ht_item	*item;

    item = (t_ht_item *) malloc(sizeof(t_ht_item));
	if (item == NULL)
		return (NULL);
    item->key = (char *) malloc(ft_strlen(key) + 1);
    item->value = (char *) malloc(ft_strlen(value) + 1);
	if (item->key == NULL || item->value == NULL)
		return (free_item_return(item));
    ft_strcpy(item->key, key);
    ft_strcpy(item->value, value);
    return (item);
}

t_hash_table	*create_table(int size)
{
    t_hash_table	*table;

	table = (t_hash_table *) malloc(sizeof(t_hash_table));
	if (table == NULL)
		return (NULL);
    table->size = size;
    table->count = 0;
    table->items = (t_ht_item **) ft_calloc(table->size, sizeof(t_ht_item *));
	if (table->items == NULL)
		return (free_htable(table));
	ft_bzero(table->items, table->size);
	table->overflow_buckets = create_overflow_buckets(table);
    return (table);
}

void	ht_insert(t_hash_table *table, char	*key, char *value)
{
	t_ht_item		*item;
	t_ht_item		*current_item;
	unsigned long	hash;

	if (table == NULL || table->items == NULL || table->size == 0)
		return ;
	item = create_item(key, value);
	if (item == NULL)
		return ;
	hash = hash_from_str(key);
	current_item = table->items[hash];
	if (current_item == NULL)
	{
		if (table->count == table->size)
			free_item(item);
		else
		{
			table->items[hash] = item;
			table->count++;
		}
	}
	else
	{
		if (ft_strcmp(current_item->key, key) == 0)
		{
			ft_strcpy(current_item->value, value);
			free_item(item);
		}
		else
			handle_collision(table, hash, item);
	}
}

char	*ht_search(t_hash_table *table, char *key)
{
	unsigned long	hash;
	t_ht_item		*item;
	t_list			*head;

	hash = hash_from_str(key);
	head = table->overflow_buckets[hash];
	item = table->items[hash];
	if (item == NULL)
		return (NULL);
	while (ft_strcmp(item->key, key) != 0)
	{
		if (head == NULL)
			return (NULL);
		item = (t_ht_item *) head->content;
		head = head->next;
	}
	return (item->value);
}
