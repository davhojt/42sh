/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_doublequote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 16:12:58 by rpinoit           #+#    #+#             */
/*   Updated: 2018/10/27 21:10:33 by dlaurent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	lexer_token_doublequote(t_lexer *lexer, const char **cmd)
{
	int	i;

	i = 0;
	*cmd = *cmd + 1;
	while (cmd[0][i] != '\"')
	{
		if (cmd[0][i] == '\0')
			return (STATUS_DQUOTE);
		++i;
	}
	lexer_token_add(lexer, *cmd, i, TOKEN_DOUBLEQUOTE);
	*cmd = *cmd + i + 1;
	return (STATUS_OK);
}