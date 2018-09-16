/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <dhojt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 11:59:00 by dhojt             #+#    #+#             */
/*   Updated: 2018/09/17 08:44:57 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool				sort_alpha(t_frame *frame)
{
	if (ft_strcmp(frame->track->data.str, frame->track->next->data.str) > 0)
		return (true);
	return (false);
}