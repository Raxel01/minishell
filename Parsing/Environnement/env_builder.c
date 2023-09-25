/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:04:00 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/25 19:07:21 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

int   ft_strchr(char *s, char c)
{
	int		i;

	i = 0;
	if (!s)
		return (404);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (404);
}

void    add_member(my_env **head_members, my_env *new_member)
{
    my_env *cursur;
    
    cursur = *head_members;
    while (cursur->next)
        cursur = cursur->next;
    cursur->next = new_member;
    new_member->prev = cursur;
}

/*************DANGER ZONE HERE USE : STRLEN***************/
my_env *build_member(char *env_member)
{
    my_env *member;
    int equal_pos;

    equal_pos = ft_strchr(env_member, '=');
    if (!(member = malloc(sizeof (my_env))))
        return (NULL);
    if (equal_pos != 404)
    {
        member->var = ft_substr(env_member, 0, equal_pos);
        member->var_content = ft_substr(env_member, equal_pos + 1, ft_strlen(env_member) - equal_pos);
    }
    else
        {
            member->var = ft_substr(env_member, 0, equal_pos);
            member->var_content = NULL;
        }
    member->m_env = NULL;
    member->next = NULL;
    member->prev=NULL;
    return(member);
}

my_env  *init_head(my_env **env_head, char ** sys_env)
{
    if (!((*env_head) = malloc(sizeof(my_env))))
        return (NULL);
    (*env_head)->m_env = sys_env;
    (*env_head)->next = NULL;
    (*env_head)->prev = NULL;
    (*env_head)->var = NULL;
    (*env_head)->var_content = NULL;
    return (*env_head);
}

my_env*    import_env(char **sys_env)
{
    my_env  *env;
    int exist;

    exist = 0;
    env = NULL;
    if (!(env = init_head(&env, sys_env)))
        return (NULL);
    while (sys_env[exist])
        add_member(&env, build_member(sys_env[exist++]));
    return (env);
}