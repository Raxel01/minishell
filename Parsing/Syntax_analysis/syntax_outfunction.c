/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_outfunction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:28:17 by abait-ta          #+#    #+#             */
/*   Updated: 2023/09/27 22:23:19 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Header/Parsing.h"

void	error_announcer(int fd, char *error)
{
	write(fd, error, ft_strlen(error));
}

t_token_list	*behind_getter(t_token_list *cursus)
{
	t_token_list	*behind;

	behind = cursus->prev;
	while (behind && behind->type == A_SPACE)
		behind = behind->prev;
	return (behind);
}

t_token_list	*forward_getter(t_token_list *cursus)
{
	t_token_list	*forward;

	forward = cursus->next;
	while (forward && forward->type == A_SPACE)
		forward = forward->next;
	return (forward);
}
