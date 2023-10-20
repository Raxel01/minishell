/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:38 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/20 17:07:55 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

int	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	bashvar_norm(char *var)
{
	int	i;

	i = 0;
	if (var[i] && (is_alpha(var[i]) || var[i] == '_'))
	{
		while (var[++i])
			if (!(is_alphanum(var[i]) || var[i] == '_'))
				return (0);
		return (1);
	}
	return (0);
}

void	unset_var(char *var_name, t_my_env **env)
{
	t_my_env	*curs;
	t_my_env	*temp;

	curs = (*env)->next;
	temp = NULL;
	while (curs != NULL)
	{
		if (ft_strcmp(curs->var, var_name) == 0)
		{
			if (curs->prev != NULL)
				curs->prev->next = curs->next;
			if (curs->next != NULL)
				curs->next->prev = curs->prev;
			if (*env == curs)
				*env = curs->next;
			temp = curs;
			curs = curs->next;
			free(temp->var);
			free(temp->var_content);
			free(temp);
		}
		else
			curs = curs->next;
	}
}

int	run_unset(char **cmd_table, t_my_env **env)
{
	int	i;

	i = 1;
	if (!cmd_table[1])
		return (0);
	while (cmd_table[i])
	{
		if (!bashvar_norm(cmd_table[i]))
			return (error_announcer(NULL, 666), 1);
		unset_var(cmd_table[i], env);
		i++;
	}
	return (0);
}
