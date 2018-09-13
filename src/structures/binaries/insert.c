/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 16:11:32 by dlaurent          #+#    #+#             */
/*   Updated: 2018/09/01 01:29:51 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bin_item	*bin_new_item(t_shell *shell, t_bin *bin, t_bin_obj *obj)
{
	t_bin_item	*item;

	if (!(item = (t_bin_item *)ft_memalloc(sizeof(t_bin_item))))
		error_malloc_bin(shell, bin, "t_bin_item structure");
	item->key = obj->name;
	item->value = obj;
	return (item);
}

t_bin_obj			*bin_new_obj(t_shell *sh, char *n, char *p, t_stat st)
{
	t_bin_obj	*obj;

	if (!(obj = (t_bin_obj *)ft_memalloc(sizeof(t_bin_obj))))
		error_malloc_bin(sh, NULL, "t_bin_obj structure");
	obj->name = ft_strdups(n);
	ft_strcpy(obj->path, p);
	obj->stats = st;
	return (obj);
}

void				bin_insert(t_shell *shell, t_bin *bin, t_bin_obj *obj)
{
	int			i;
	int			index;
	t_bin_item	*item;
	t_bin_item	*current_item;
	t_bin_item	deleleted_item;

	i = 1;
	deleleted_item.key = NULL;
	deleleted_item.value = NULL;
	item = bin_new_item(shell, bin, obj);
	index = bin_get_hash(item->key, bin->size, 0);
	current_item = bin->items[index];
	while (current_item)
	{
		if (current_item != &deleleted_item
		&& !ft_strcmp(current_item->key, obj->name))
		{
			bin->items[index] = item;
			return (bin_delete_specified_item(current_item));
		}
		index = bin_get_hash(item->key, bin->size, i++);
		current_item = bin->items[index];
	}
	bin->items[index] = item;
	bin->count++;
}