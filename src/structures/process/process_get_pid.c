/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_get_pid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhojt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 15:41:03 by dhojt             #+#    #+#             */
/*   Updated: 2018/11/04 16:10:55 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_process			*process_get_pid(t_shell *sh, pid_t pid)
{
	return (process_get(sh, 0, pid));
}
