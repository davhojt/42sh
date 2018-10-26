/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlaurent <dlaurent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/13 01:28:20 by dlaurent          #+#    #+#             */
/*   Updated: 2018/10/26 02:30:04 by dhojt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char			*get_auto_mode(t_shell *sh, char *content)
{
	char			*str;

	if (!(str = ft_strrchr(move_past_leading_spaces(content), ' ')))
	{
		str = move_past_leading_spaces(content);
		sh->ac->auto_mode = (*str != '.') ? AUTO_BIN : AUTO_REG;
		if (*str == '$' && (sh->ac->auto_mode = AUTO_ENV) == AUTO_ENV)
			str++;
	}
	else
	{
		str++;
		if (*str == '$' && (sh->ac->auto_mode = AUTO_ENV) == AUTO_ENV)
			str++;
		else
			sh->ac->auto_mode = AUTO_REG;
	}
	if (!contains_printable_characters(content)
			|| sh->ac->auto_mode == AUTO_NON)
		return (NULL);
	return (str);
}

static char			*get_env_var(t_shell *sh, char *ptr_to_dollar, int len)
{
	char			**environment;
	char			*env;
	int				total;

	total = 0;
	env = NULL;
	environment = sh->env->environment;
	while (*environment)
	{
		if (!ft_strncmp(*environment, ptr_to_dollar + 1, len - 1))
		{
			env = *environment;
			if (++total > 1)
				return (NULL);
		}
		environment++;
	}
	return (env);
}

static bool			auto_env(t_shell *sh)
{
	int				len;
	char			*env;
	char			*track;
	char			*ptr_dollar;

	if ((ptr_dollar = ft_strrchr(sh->buffer.content + sh->buffer.ushift, ' ')))
		ptr_dollar++;
	else
		ptr_dollar = sh->buffer.content + sh->buffer.ushift;
	if (*ptr_dollar != '$')
		return (false);
	len = ft_strlen(ptr_dollar + 1) + 1;
	if (!(env = get_env_var(sh, ptr_dollar, len)) || !ft_strchr(env, '=')
			|| ft_strncmp(env, ptr_dollar + 1, ft_strchr(env, '=') - env)
			|| !(env = ft_strchr(env, '=') + 1))
		return (false);
	track = sh->buffer.content + sh->buffer.ushift;
	sh_move_home(sh);
	while (track++ != ptr_dollar)
		sh_move_right(sh);
	while (len--)
		sh_delete_current_char(sh);
	sh_print_str(sh, env);
	sh_move_end(sh);
	return (true);
}

bool				try_expansions(t_shell *sh)
{
	return (auto_glob(sh) || auto_history(sh) || auto_env(sh));
}

/*
** #PARAMS
** performed_completion: status of is an expansion or autocompletion did happen
** parsed_buffer: partial file name. if buffer == libft/sr parsed_buffer = sr
**
** #RETURN
** bool - status of auto_completion. Returns true only if some auto completion
** or expansion was succesfuk.
**
** auto_completion mode informs window resize to print auto_completion display
**
** auto completion happends only if no expansion was successful and that
** tab was pressed.
**
** move cursor to end. auto completion only works with last item in buffer.
**
** auto_issuance only launches if all mallocs were successful
*/

bool				auto_completion(t_shell *sh)
{
	bool			performed_completion;
	char			*parsed_buffer;

	performed_completion = false;
	sh->modes.auto_completion = TRUE;
	if (try_expansions(sh))
		performed_completion = true;
	else if (!ft_strcmps(sh->read->line, K_TAB))
	{
		sh_move_end(sh);
		if (!(sh->ac = (t_ac *)malloc(sizeof(t_ac))))
			return (false);
		ft_bzero(sh->ac, sizeof(t_ac));
		if (!(parsed_buffer = get_auto_mode(
			sh,
			sh->buffer.content + sh->buffer.ushift)))
			return (false);
		sh->ac->initial_file_name = parsed_buffer;
		if (auto_get_obj(sh))
			auto_issuance(sh);
		auto_free_ac(sh);
		performed_completion = true;
	}
	sh->modes.auto_completion = FALSE;
	return (performed_completion);
}
