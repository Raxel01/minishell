/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exported_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 20:40:31 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/23 20:42:49 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

t_my_env    *duplicate_env(t_my_env **original)
{
    t_my_env	*dup_head;
    t_my_env	*duped_node;
	t_my_env	*current;
	t_my_env	*previ;
	
	dup_head = NULL;
	previ = NULL;
    current = (*original)->next;
    while (current)
	{
        duped_node = creatdup(current->var, current->var_content);
        if (duped_node == NULL)
            return NULL;
		if (!previ)
            dup_head = duped_node;
		else
            previ->next = duped_node;
        previ = duped_node;
		current = current->next;
    }
    return (dup_head);
}

t_my_env    *creatdup(char *var, char *var_content)
{
	t_my_env	*duped_node;
	
	duped_node = (t_my_env *)malloc(sizeof(t_my_env));
    if (duped_node == NULL)
        return NULL;
    duped_node->var = ft_strdup(var);
    duped_node->var_content = ft_strdup(var_content);
    duped_node->m_env = NULL;
    duped_node->next = NULL;
    duped_node->prev = NULL;
	return (duped_node);
}

void    sorting(t_my_env *env)
{
	t_my_env	*circl;
	
	circl = env->next;
	while(circl->next)
	{
		if (ft_strcmp(circl->var, circl->next->var) > 0)
		{
			regulateur(circl, circl->next);
			circl = env;
		}
		else
			circl = circl->next;
	}
}

char    *ft_strdup(char *s)
{
	char	*ptr;
	size_t	len ;
	size_t	i;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 1;
	i = 0;
	ptr = (char *)malloc (len * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	regulateur(t_my_env *curs, t_my_env *next)
{
	char	*t_key;
	char	*t_value;

	t_key = curs->var;
	curs->var = next->var;
	next->var = t_key;
	t_value = curs->var_content;
	curs->var_content = next->var_content;
	next->var_content = t_value;
}
