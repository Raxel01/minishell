/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 21:49:49 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/24 19:02:20 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"
/*DANGER USING STRCMP OF LIBRARY*/
char *replaceby_content(char *search_for, my_env **env)
{
    my_env *cursus;

    cursus = (*env)->next;
    while (cursus)
    {
        if (!strcmp(search_for + 1, cursus->var))
        {
            free(search_for);
            return (ft_strndup(cursus->var_content, ft_strlen(cursus->var_content)));
        }
        cursus = cursus->next;
    }
    return (ft_strndup("", ft_strlen("")));
}

void    env_var_expansion(t_token_list **tokens, my_env **env)
{
    t_token_list *cursur;

    cursur = (*tokens);
    while (cursur)
    {
        if (cursur->state ==IN_DQUOT && (cursur->type == ENV_VAR || cursur->type == SPECIAL_VAR))
        {
            cursur->token = replaceby_content(cursur->token, env);
            cursur->type = WORD;
        }
        cursur = cursur->next;
    }
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        char                    *str;
        unsigned int    i;
        unsigned int    j;

        if (s)
        {
                i = start;
                j = 0;
                str = (char *)malloc(sizeof(char) * (len +1));
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
        member->var_content = ft_substr(env_member, equal_pos + 1, strlen(env_member) - equal_pos);
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

void    add_member(my_env **head_members, my_env *new_member)
{
    my_env *cursur;
    
    cursur = *head_members;
    while (cursur->next)
        cursur = cursur->next;
    cursur->next = new_member;
    new_member->prev = cursur;
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

void    print_env(my_env **env)
{
    my_env *cursur;

    cursur = *env;
    while (cursur)
    {
        printf ("var :|%s|\nvar_content : |%s|\n\n", cursur->var, cursur->var_content);
        cursur = cursur->next;
    }
}

void    free_env(my_env **env)
{
    my_env *cursur;
    
    while (*env)
    {
        cursur = *env;
        (*env) =  (*env)->next;
        free(cursur->var);
        free(cursur->var_content);
        free(cursur);
    }
    
}