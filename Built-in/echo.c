/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:40:19 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/13 11:29:21 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Header/Parsing.h"

int option_n(char *elem)
{
    int i = 0;
    
    if (elem && elem[i] && elem[i] == '-' && elem[i + 1])
    {
        while (elem[++i])
            if (elem[i] != 'n')
                return (0);
        return (1);
    }
    return (0);
}

int run_echo(char **cmd_table)
{
	int	i;
	int	_n;

	i = 1;
	_n = 0;
	while (cmd_table[i] && option_n(cmd_table[i]))
	{
		_n = 1;
		i++;
	}
	while (cmd_table[i])
	{
		write(1, cmd_table[i], ft_strlen(cmd_table[i]));
		if (cmd_table[i + 1])
			write(1, " ", 2);
		i++;
	}
	if (_n == 0)
		write(1, "\n", 2);
	return (0);
}
