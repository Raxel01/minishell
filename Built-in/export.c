/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:32 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/23 23:04:11 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

void	view_exportedvar(t_my_env **env)
{
	t_my_env *begin;
	t_my_env *dup_env;
	
	dup_env = duplicate_env(env);
	begin = dup_env; 
	sorting(dup_env);
	while (dup_env)
	{
		write(1, "declare -x ", 12);
		write(1, dup_env->var, ft_strlen(dup_env->var));
		if (dup_env->var_content)
		{
			write(1, "=", 2);
			write(1, "\"", 2);
			write(1, dup_env->var_content, ft_strlen(dup_env->var_content));
			write(1, "\"", 2);
		}
		write(1, "\n", 2);
		dup_env = dup_env->next;
	}
	free_env(&begin);
}

char	*standard_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char )c)
			return ((char *)(s + i + 1));
		i++;
	}
	return (NULL);
}

int		new_strchr(char *s, char c, int *mode)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (i != 0 && s[i -1] == '+')
			{
				*mode = M_APPEND;
				return(i - 1);
			}
			*mode = M_ECRASE;
			return (i);
		}
		i++;
	}
	return (ft_strlen(s));
}

void	init_elem(t_export *export, char *args)
{
	export->elem_name = NULL;
	export->elem_value = NULL;
	export->mode = 0;
	export->elem_name = ft_substr(args, 0, \
			new_strchr(args, '=', &export->mode));
	export->elem_value = standard_strchr(args, '=');
}

/*printf("var:%s*-->%s|-->mode:%d\n",*/
/* e.elem_name, e.elem_value, e.mode);*/
int	run_export(char **cmd_table, t_my_env **env)
{
	int			i;
	t_export	e;
	
	if (!cmd_table[1])
		return (view_exportedvar(env), 0);
	i = 0;
	while (cmd_table[++i])
	{
		init_elem(&e, cmd_table[i]);
		if (bashvar_norm(e.elem_name))
		{
			if (search(e.elem_name, env))
				modifyenv(e, env);
			else
				addenvmember(e, env);
			free(e.elem_name);
		}
		else
			return (free(e.elem_name), \
				error_announcer("elem:not a valid identifier\n", 0), NOT_VALID);
	}
	return (0);
}
