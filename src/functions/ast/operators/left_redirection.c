/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azaliaus <azaliaus@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:44:04 by azaliaus          #+#    #+#             */
/*   Updated: 2018/10/28 18:17:16 by azaliaus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	single_left_cursor(t_shell *sh, t_token_tree *tree, int fd)
{
	int		stdin;
	char	ret;

	stdin = dup(0);
	dup2(fd, 0);
	ret = execute_tree(sh, tree->left);
	dup2(stdin, 0);
	close(stdin);
	close(fd);
	return (ret);
}

char		execute_left_redirection(t_shell *sh, t_token_tree *tree)
{
	int					fd;
	int					type;
	int					hdoc_count;
	char				*file;
	t_token_tree		*last;

	last = tree->right;
	type = ((!ft_strcmp(tree->tokens[0], "<<")) ? 2 : 1);
	hdoc_count = (type == 2 ? 1 : 0);
	while (last)
	{
		file = (last->left) ? last->left->tokens[0] : last->tokens[0];
		if (type == 1 && ((fd = open(file, O_RDONLY)) == -1))
			return (error_execution_file(sh, file));
		(last->left && last->right) ? close(fd) : 0;
		if (last->right)
		{
			type = (!ft_strcmp(tree->tokens[0], "<<") ? 2 : 1);
			hdoc_count += (type == 2 ? 1 : 0);
		}
		last = last->right;
	}
	if (type == 1)
		return (single_left_cursor(sh, tree, fd));
	return (left_heredoc(sh, tree, hdoc_count));
}