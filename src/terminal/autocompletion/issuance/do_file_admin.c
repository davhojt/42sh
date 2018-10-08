/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_file_admin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/13 14:15:36 by dhojt             #+#    #+#             */
/*   Updated: 2018/10/08 08:43:52 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "auto_completion.h"
#include "auto_completion_prot.h"

static void			get_mode(t_shell *sh, t_obj *head)
{
	t_obj			*obj;

	obj = head;
	while (sh->ac->cmp_mode == MODE_NON && obj)
	{
		if (!obj->data.no_file)
			if (!ft_strncmp(obj->data.str, sh->ac->file_name,
						sh->ac->file_name_len))
				sh->ac->cmp_mode = MODE_CMP;
		obj = obj->next;
	}
	obj = head;
	while (sh->ac->cmp_mode == MODE_NON && obj)
	{
		if (!obj->data.no_file)
			if (ft_strstr(obj->data.str, sh->ac->file_name))
				sh->ac->cmp_mode = MODE_STR;
		obj = obj->next;
	}
}

static void			lock_files(t_shell *sh, t_obj *obj)
{
	while (obj)
	{
		if (sh->ac->cmp_mode == MODE_CMP)
		{
			if (ft_strncmp(obj->data.str, sh->ac->file_name,
						sh->ac->file_name_len))
				obj->data.no_file = 1;
		}
		if (sh->ac->cmp_mode == MODE_STR)
		{
			if (!ft_strstr(obj->data.str, sh->ac->file_name))
				obj->data.no_file = 1;
		}
		if (!ft_strcmps(obj->data.str, "."))
			obj->data.no_file = 1;
		obj = obj->next;
	}
}

static void			get_column_widths(t_shell *sh, t_obj *obj)
{
	t_obj			*head;

	sh->ac->len_file_name = 0;
	sh->ac->items_to_display = 0;
	sh->ac->total_blocks = 0;
	head = obj;
	while (head)
	{
		if (!head->data.no_file)
		{
			auto_calc_len_file_name(sh, head);
			head->data.file_number = sh->ac->items_to_display;
			sh->ac->items_to_display++;
		}
		head = head->next;
	}
}

static void			issue_circular_pointers(t_shell *sh, t_obj *head)
{
	t_obj			*obj;
	t_obj			*track;

	while (head->next && head->data.no_file)
		head = head->next;
	obj = head;
	sh->ac->select = head;
	sh->ac->select->data.file_number = 0;
	while (obj && obj->next)
	{
		track = obj->next;
		while (track && track->data.no_file)
			track = track->next;
		if (!track)
			break ;
		track->ver_prev = obj;
		obj->ver_next = track;
		track->data.file_number = obj->data.file_number + 1;
		obj = track;
	}
	obj->ver_next = head;
	head->ver_prev = obj;
}

void				auto_do_file_admin(t_shell *sh, t_obj *obj)
{
	get_mode(sh, obj);
	lock_files(sh, obj);
	get_column_widths(sh, obj);
	issue_circular_pointers(sh, obj);
}
