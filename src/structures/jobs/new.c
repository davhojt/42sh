/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 14:01:39 by azaliaus          #+#    #+#             */
/*   Updated: 2018/11/05 16:41:20 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_job		*job_new(void)
{
	t_job		*job;

	if (!(job = (t_job *)ft_memalloc(sizeof(t_job))))
		return (NULL);
	job->fd[0] = 0;
	job->fd[1] = 1;
	job->fd[2] = 2;
	job->next = NULL;
	return (job);
}
