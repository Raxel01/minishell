/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukaiz <mboukaiz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:21:44 by mboukaiz          #+#    #+#             */
/*   Updated: 2023/11/10 03:09:05 by mboukaiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/execution.h"

char	**dup_func(t_my_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->var, "PATH"))
			break ;
		env = env->next;
	}
	if (env)
		return (ft_split(env->var_content, ':'));
	return (NULL);
}

void	copy_str(char *s1, char **key, char **value)
{
	int		i;
	int		j;
	int		key_length;
	int		value_length;

	str_length(s1, &key_length, &value_length);
	(*key) = malloc (key_length + 1);
	(*value) = malloc (value_length + 1);
	i = 0;
	j = key_length + 1;
	while (key_length--)
	{
		(*key)[i] = s1[i];
		i++;
	}
	(*key)[i] = '\0';
	i = 0;
	while (value_length--)
	{
		(*value)[i] = s1[i + j];
		i++;
	}
}

void	str_length(char *s1, int *key_length, int *value_length)
{
	int		key_l;
	int		value_l;

	key_l = 0;
	value_l = 0;
	while (s1[key_l] != '=' && s1[key_l])
		key_l++;
	while (s1[key_l + value_l])
	{
		value_l++;
	}
	*key_length = key_l;
	*value_length = value_l;
}

char	*find_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
		i++;
	}
	return (ft_strdup("\0"));
}
