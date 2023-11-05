/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:49:49 by abait-ta          #+#    #+#             */
/*   Updated: 2023/11/05 12:33:00 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (404);
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

/*DANGER USING STRCMP OF LIBRARY*/
char	*replaceby_content(char *search_for, t_my_env **env)
{
	t_my_env	*cursus;

	cursus = (*env)->next;
	while (cursus)
	{
		if (!ft_strcmp(search_for + 1, cursus->var))
		{
			free(search_for);
			return (ft_strndup(cursus->var_content, \
					ft_strlen(cursus->var_content)));
		}
		cursus = cursus->next;
	}
	free(search_for);
	return (ft_strndup("", ft_strlen("")));
}

/*Made changes here don't expand << $PATH */
void	env_var_expansion(t_token_list **tokens, t_my_env **env)
{
	t_token_list	*cursur;
	t_token_list	*prev;

	cursur = (*tokens);
	while (cursur)
	{
		if (cursur->type == ENV_VAR || cursur->type == SPECIAL_VAR)
		{
			if (cursur->prev)
			{
				prev = behind_getter(cursur);
				if (prev->type == HERE_DOC)
				{
					cursur->type = WORD;
					cursur = cursur->next;
					continue ;
				}
			}
			cursur->token = replaceby_content(cursur->token, env);
			cursur->type = WORD;
		}
		cursur = cursur->next;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;
	unsigned int	j;

	if (s)
	{
		i = start;
		j = 0;
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		while (s[i] && i < (len + start))
		{
			str[j++] = s[i++];
		}
		str[j] = '\0';
		return (str);
	}
	return (NULL);
}

void	free_env(t_my_env **env)
{
	t_my_env	*cursur;

	while (*env)
	{
		cursur = *env;
		(*env) = (*env)->next;
		free(cursur->var);
		free(cursur->var_content);
		free(cursur);
	}
}
