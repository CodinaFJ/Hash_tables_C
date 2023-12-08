/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcodina- <fjavier.codina@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:29:37 by jcodina-          #+#    #+#             */
/*   Updated: 2023/12/08 11:29:37 by jcodina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _HASH_TABLE_H
# define _HASH_TABLE_H
# define HT_CAPACITY 50000
# include "../lib/libft/libft.h"
# include "../lib/ft_printf/ft_printf.h"

typedef struct s_ht_item
{
    char*	key;
    char*	value;
}		t_ht_item;

typedef struct s_hash_table
{
    t_ht_item	**items;
	t_list		**overflow_buckets;
    size_t		size;
    size_t			count;
}		t_hash_table;

/* ************************************************************************** */
/*  Hash table																  */
/* ************************************************************************** */

t_ht_item		*create_item(char *key, char *value);
t_hash_table	*create_table(int size);
void			ht_insert(t_hash_table *table, char	*key, char *value);
char			*ht_search(t_hash_table *table, char *key);

/* ************************************************************************** */
/*  Hash table utils														  */
/* ************************************************************************** */

unsigned long	hash_from_str(char *str);
void			ht_delete(t_hash_table *table, char *key);

/* ************************************************************************** */
/*  Hash table collisions													  */
/* ************************************************************************** */

t_list			**create_overflow_buckets(t_hash_table *table);
void			free_overflow_buckets(t_hash_table *table);
void			handle_collision(t_hash_table *table,
					unsigned long hash,
					t_ht_item *item);

/* ************************************************************************** */
/*  Hash table management													  */
/* ************************************************************************** */

void			free_item(void *item);
void			*free_item_return(void *item);
void			*free_htable(t_hash_table *table);
void			print_table(t_hash_table *table);
void			print_search(t_hash_table* table, char* key);

#endif