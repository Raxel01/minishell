/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exportmodify_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 22:56:45 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/23 22:58:32 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

short	search(char *elem, t_my_env **env)
{
	t_my_env	*current;

	current = (*env)->next;
	while(current)
	{
		if (!ft_strcmp(elem, current->var))
			return (1);
		current = current->next;
	}
	return (0);
}

void	appendmode(t_export e, t_my_env **env)
{
	t_my_env *curs;
	
	curs = (*env)->next;
	while(curs)
	{
		if (!ft_strcmp(e.elem_name, curs->var))
			curs->var_content = ft_strjoin(curs->var_content, e.elem_value);
		curs = curs->next;
	}
}

void	ecrasmode(t_export e, t_my_env **env)
{
	t_my_env *curs;
	
	curs = (*env)->next;
	while(curs)
	{
		if (!ft_strcmp(e.elem_name, curs->var))
		{
			free(curs->var_content);
			curs->var_content = ft_strdup(e.elem_value);
		}
		curs = curs->next;
	}
}

void	modifyenv(t_export e , t_my_env **env)
{
	if (e.elem_value)
	{
		if (e.mode == M_ECRASE)
			ecrasmode(e, env);
		else if (e.mode == M_APPEND)
			appendmode(e, env);
	}
}
