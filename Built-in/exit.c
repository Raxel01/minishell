/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:14:28 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/11 20:59:26 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

unsigned char  to_uns(unsigned char c)
{
    status_setter(c);
    return (c);
}

int integer(char *integer)
{
    int i;
    
    i = 0;
    if (integer[i] == '-')
        i++;
    while (integer[i])
    {
        if (integer[i] < '0' || integer[i] > '9')
                return (0);
        i++;
    }
    return (1);
}
/*Grammer exit ![[+][-]exit_status]*/
// recheck status when go to school
/*DANGER ZONE USING ATOI*/
int    run_exit(char **cmd_table, t_my_env **env)
{
    write(1, "exit\n", 6);
    if (!cmd_table[1])
    {
        free_env(env);
        exit(0);
    }
    if (cmd_table[1] && cmd_table[2])
    {
        error_announcer("exit: too many arguments\n", 0);
        status_setter(1);
        free_env(env);
        exit(1);
    }
    if (cmd_table[1] && integer(cmd_table[1]))
    {
        exit(to_uns(atoi(cmd_table[1])));
        free_env(env);
    }
    else
    {
            error_announcer("exit: n: numeric argument required", 0);
            status_setter(2);
            free_env(env);
            exit(2);
    }
   return (0); 
}