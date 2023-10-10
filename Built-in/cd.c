/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:09 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/10 12:50:36 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

int builtin_recognizer(char **cmd_table, t_my_env **env)
{
    if (cmd_table[0] && ft_strcmp(cmd_table[0], "pwd") == 0)
        return (status_setter(run_pwd(cmd_table)), 1);
    else if (cmd_table[0] && ft_strcmp(cmd_table[0], "echo") == 0)
        return (status_setter(run_echo(cmd_table)), 1);
    else if (cmd_table[0] && ft_strcmp(cmd_table[0], "cd") == 0)
        return (status_setter(run_cd(cmd_table, env)), 1);
    // else if (cmd_table[0] && ft_strcmp(cmd_table[0], "export") == 0)
    //     return (status_setter(run_export(cmd_table, env)), 1);
    // else if (cmd_table[0] && ft_strcmp(cmd_table[0], "unset") == 0)
    //     return (status_setter(run_unset(cmd_table, env)), 1);
    else if (cmd_table[0] && ft_strcmp(cmd_table[0], "env") == 0)
        return (status_setter(run_env(cmd_table, env)), 1);
    // else if (cmd_table[0] && ft_strcmp(cmd_table[0], "exit") == 0)
    //     return (status_setter(run_exit(cmd_table, env)), 1);
    return (0);
}

void    env_updater(t_my_env **env, char *to_update, char *update_by)
{
    t_my_env *curs;

    curs = *env;
    while (curs)
    {
        if (ft_strcmp(to_update, curs->var))
        {
            printf("\nto_update : %s | update_By : %s\n", to_update, update_by);
            free(curs->var_content);
            curs->var_content = ft_strndup(update_by, ft_strlen(update_by));
            return;
        }
        curs = curs->next;
    }
}
/*USE PATH MAX IN sted OF 1024*/
char    *get_cwd()
{
    char *my_dir;

    my_dir = getcwd(NULL, 1024);
    if (!my_dir)
        status_setter(1);
    return (my_dir);
}

// should free existing dir;
int    goto_new_dir(char *tonew_path, t_my_env **env)
{
    char *existin_dir;
    
    existin_dir = get_cwd();
    printf ("existing dir : %s \n", existin_dir);
    if (chdir(tonew_path) == -1)
    {
            free(existin_dir);
            return(error_announcer("no such file or directory", 0), 1);
    }
    else
    {
        /*UPDATE oldpwd*/
        /*SET_NEW : PWD*/
        env_updater(env, "OLDPWD", existin_dir);
        env_updater(env, "PWD", tonew_path);
        // status_setter(0);
        return (0);
    }
}

char *home_value(t_my_env **env)
{
    t_my_env *curs;

    curs = *env;
    while (curs)
    {
        if (ft_strcmp("HOME", curs->var) == 0)
            return (ft_strndup(curs->var_content, ft_strlen(curs->var_content)));
        curs = curs->next;
    }
    return (NULL);
}
/*no_option alloced free it */
int    run_cd(char **cmd_table, t_my_env **env)
{
    char *no_option;
    
    if (!cmd_table[1])
    {
        no_option = home_value(env);
        printf("home_value: %s\n", no_option);
        if (!no_option)
            return (error_announcer("cd : HOME not set\n", 0), 1);
        return (goto_new_dir(no_option, env));
    }
       return (113); 
}