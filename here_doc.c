/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 14:24:35 by abait-ta          #+#    #+#             */
/*   Updated: 2023/10/14 22:33:00 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./Header/Parsing.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

int	ft_strcmpo(char *s1, char *s2)
{
	int	i;
	
	i = 0;
	if (!s1 || !s2)
		return (404);
	while (s1 && s2 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int    here_doc_(char *delim)
{
    int fd;
    
    fd = open("NEW_test", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
        return(printf("fd open= -1"), -1);
    char content[1027];
    ssize_t bytes_readed;
    while(1)
    {
        write(1, "> ", 3);
        bytes_readed = read(0, content, 1027);
        if (bytes_readed == -1)
            return(printf("read = -1"), -1);
        content[bytes_readed] = '\0';
        write(0, content, strlen(content));
        if (ft_strcmpo(content, delim) == 0)
            break;
    }
    return (fd);
}

int	heredoc(char *delim)
{
	int		hfd[2];
	int		len;
	char	*buff;

	if (!delim || pipe(hfd) == -1)
		return (-1);
	len = strlen(delim);
	while (1)
	{
		buff = readline("> ");
		if (!buff || memcmp(delim, buff, len + 1) == 0)
			break ;
		write(hfd[1], buff, strlen(buff));
		write(hfd[1], "\n", 1);
	}
	return (close(hfd[1]), hfd[0]);
}

int main(int ac , char **av) {
    // int fd =  heredoc("$PATH");
    // if (fd == -1) {
    //     perror("Error opening the file");
    //     return 1;
    // }
    // dup2(fd , 0);
    // // close(0);
    // char *cmd[] = {"awk", "{print $1}", NULL};
    // execve("/usr/bin/awk", cmd, NULL);
    printf ("ABDELALI\n");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    
    return 0;
}
