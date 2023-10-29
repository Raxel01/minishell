/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:03:14 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/29 16:03:25 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

char	*pushcontent_clean(int heredoc, char *readed_data)
{
	write(heredoc, readed_data, ft_strlen(readed_data));
	write(heredoc, "\n", 1);
	free(readed_data);
	return (NULL);
}

void	free_elem(char *eof, char *index)
{
	free(eof);
	free(index);
}
