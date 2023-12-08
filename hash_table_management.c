/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:20:03 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/08 12:20:03 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"

void	free_item(void *item)
{
	t_ht_item *ht_item;

	ht_item = (t_ht_item *) item;
	if (ht_item == NULL)
		return ;
	if (ht_item->key != NULL)
	{
    	free(ht_item->key);
		ht_item->key = NULL;
	}
	if (ht_item->value != NULL)
	{
    	free(ht_item->value);
		ht_item->value = NULL;
	}
	free(ht_item);
	ht_item = NULL;
}

void	*free_item_return(void *item)
{
	free_item(item);
	return (NULL);
}

void	*free_htable(t_hash_table *table)
{
	size_t		i;

	i = 0;
	if (table == NULL)
		return (NULL);
	if (table->items != NULL)
	{
		while (i < table->size)
		{
			free_item(table->items[i]);
			i++;
		}
    	free(table->items);
	}
	if (table->overflow_buckets != NULL)
		free_overflow_buckets(table);
    free(table);
	return (NULL);
}

void	print_table(t_hash_table *table)
{
	size_t	i;

	if (table == NULL)
	{
		printf("\nHash Table\n-------------------\nNULL TABLE\n");
		printf("-------------------\n\n");
		return ;
	}
	i = 0;
	printf("\nHash Table\n-------------------\n");
	while (i < table->size)
	{
		if (table->items && table->items[i])
        {
            printf("Index:%lld, Key:%s, Value:%s\n",
				i,
				table->items[i]->key,
				table->items[i]->value);
        }
		i++;
	}
	printf("-------------------\n\n");
}

void	print_search(t_hash_table* table, char* key)
{
    char* val;

	val = ht_search(table, key);
    if (val == NULL)
        printf("Key:%s does not exist\n", key);
    else
        printf("Key:%s, Value:%s\n", key, val);
}