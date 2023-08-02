#include <unistd.h>
#include "../Header/header.h"
#include   <string.h>

static int      ft_words(char const *s, char c)
{
        int     i;
        int     words;

        if (s[0] == '\0')
                return (0);
        words = 0;
        i = 0;
        while (s[i] == c) //doz delim
                i++;
        while (s[i])
        {
                if (s[i] == c && s[i - 1] != c)
                        words++;
                i++;
        }
        if (s[i - 1] != c)
                words++;
        return (words);
}

static char     *next_word(char *str, char c, int *len)
{
        int             i;
        char    *tmp;
        int             count;

        i = 0;
        count = 0;
        while (str[i] && str[i] == c)
                i++;
        tmp = &str[i];
        while (str[i] && str[i] != c)
        {
                count++;
                i++;
        }
        *len = count;
        return (tmp);
}

static char     **ft_freetab(char **str, int tofree)
{
        while (--tofree >= 0)
                free(str[tofree]);
        free(str);
        str = NULL;
        return (str);
}

char    **ft_split(char const *s, char c)
{
        int             i;
        char    **str;
        char    *tmp;
        int             words;
        int             len;

        if (!s)
                return (NULL);
        i = -1;
        words = ft_words(s, c);
        str = (char **)malloc(sizeof(char *) * (words + 1));
        if (!str)
                return (NULL);
        tmp = (char *)s;
        len = 0;
        while (++i < words)
        {
                tmp = next_word(tmp + len, c, &len);
                str[i] = (char *)malloc(len + 1);
                if (!str[i])
                        return (ft_freetab(str, i));
                // strlcpy(str[i], tmp, len + 1);
        }
        str[i] = 0;
        return (str);
}

int ft_metacaracters(char input)
{
    char *meta;
    meta = " |&;()<>";
    int i;

    i = 0;
    while (meta[i])
    {
        if (meta[i] == input)
            return (1);
        i++;
    }
return (0);
}

// void    Lexical_analysis(char *data)
// {
//     char *start;
//     int trimer_max;
//     start = trim_from_end(data,' ');
//     while (*data)
//     {
//         while(ft_metacaracters(*data))
//             data++;
//         if (*data == ' ' && data < start )
//             write(1, "\n", 1);
//         write(1, data, 1);
//         data++;
//     }
// }

void    get_content_single_quotes(char *commande)
{
    while ((*commande) && *(commande) != '\'')
        commande++;
    if(*commande && (*commande) == '\'')
        commande++;
    while ((*commande) && (*commande) != '\'')
    {
        write(1, commande,1);
        commande++;
    }
    write(1, "  ", 1);
}

char *return_string_epured(char *data)
{
    return (data);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	else
		return (0);
}

void get_token(char *commande_line, int *len, char *breaker)
{
    while (commande_line && *commande_line)
    {
        if (ft_metacaracters(*commande_line))
            commande_line++;
        write(1, commande_line, 1);
        commande_line++;
    }
}

int token_counter(char *string, char delimiter)
{
    int total_word;
    total_word = 0;
    while(*string)
    {
        if ((!ft_metacaracters(*string) && ft_metacaracters(*(string + 1)) || (!ft_metacaracters(*string) && *(string + 1) == '\0')))
                total_word++;
            string++;
    } 
    return (total_word);
}

char *epur_string(char *commande)
{
	int i;
	int flg = 0;
    char *epured_string = malloc(sizeof(char) * strlen(commande));
    char *begin = epured_string;
    i = 0;
	
	while (commande[i] && (commande[i] == ' ' || commande[i] == '\t'))
			++i;
	while (commande[i])
		{
			if (commande[i] == ' ' || commande[i] == '\t')
				flg = 1;
			if (!(commande[i] == ' ' || commande[i] == '\t'))
			{
				if (flg)
					{
                        *epured_string = ' ';
                        epured_string++;
                    }
				flg = 0;
				*epured_string = commande[i];
                epured_string++;
			}
			i += 1;
		}
        *epured_string = '\0';

	return (begin);
}

void    laeks()
{
    system("leaks a.out");
}

size_t  ft_strlen(const char *s)
{
        size_t  i;

        i = 0;
        while (s[i])
                i++;
        return (i);
}

char    *ft_strdup(const char *s)
{
        char    *ptr;
        size_t  len ;
        size_t  i;

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

char    *ft_substr(char const *s, size_t start, size_t len)
{
        char                    *str;
        unsigned int    i;
        unsigned int    j;

        if (s)
        {
                i = start;
                j = 0;
                if (start >= ft_strlen(s))
                        return (ft_strdup(""));
                if (len >= ft_strlen(s))
                        len = ft_strlen(s);
                str = (char *)malloc(sizeof(char) * ((len -start)+1));
                if (!str)
                        return (NULL);
                while (s[i] && i < len) // start = 5, len == 6 , start = len - 1; i < len + start
                {
                        str[j++] = s[i++];
                }
                str[j] = '\0';
                return (str);
        }
        return (NULL);
}

// void    testing(char *commande)
// {
//     char *end = commande+ft_strlen(commande) -1;
//     char *begin = commande;
//     while (commande && *commande)
//     {
//         if (*commande == '\'' || *commande == '\"')
//         {
//             if (*commande == '\'')
//             {
//                 commande++;
//                 while (*commande != '\'')
//                     commande++;
//             }
//             else
//             {
//                 commande++;
//                 while (*commande != '\"')
//                 commande++;
//             }
//         }
//         if (*commande == ' ')
//            *commande = '#';
//        commande++;
//     }
// }

int 	extract_special_token(char *commande, char search_for, int j,int i)
{
	if (search_for == '\'' || search_for == '\"')
	{
		if (search_for == '\'')
		{
			i = j;
			j++;
			while (commande[j] != '\'')
				j++;
			ft_substr(commande, i , j);
		}
		else if (search_for == '\"')
		{
			i = j;
			j++;
			while (commande[j] != '\"')
				j++;
			ft_substr(commande, i , j);
		}

	}

	return (j);
}

void    Tokenizer(char *commande)
{
	int i = 0;
	int j = 0;
	int flag;

	flag = 0;
	while(commande[j] && (j) < ft_strlen(commande))
	{
		flag = 0;
		i = j;
		j = extract_special_token(commande,commande[j], j,i);
			while (!ft_metacaracters(commande[j]) && j < ft_strlen(commande))
			{
				flag = 1;
				++j;
			}
			if (flag)
				printf ("%s\n", ft_substr(commande, i,j));
			if(ft_metacaracters(commande[j]) && j < ft_strlen(commande))
			{
				i = j;
				++j;
				printf ("%s\n", ft_substr(commande, i,j));
			}
		j--;
		j++;
	}
}

char *ft_strndup(char *to_dup, int len)
{
	int i;
	char *duped;
	i = 0;
	duped = malloc(sizeof(char) * (len + 1));
	if (!duped)
		return (NULL);
	while (to_dup[i] && i < len)
	{
	printf ("Hi\n");
		duped[i] = to_dup[i];
		i++;
	}
	duped[i] = '\0';
	return(duped);
}

int main (int ac, char **av,char **env)
{
	t_token_list *node_tokens;
    t_commande commande;
	
	node_tokens = NULL;
	// init_
    // enum token_type begin;
	// begin = rl_vi_bWord()
    int j = 0;
	int i = 0;
    while (1)
    {
        commande.commande = readline("MINISHELL[~] -> ");
        if (commande.commande == NULL)
            return (0);
		commande.commande = epur_string(commande.commande);
		Tokenizer(commande.commande);
    }
	// char *to_dup = "ls -la | wc -l | awk '{print $1}'";
	// printf ("%s", ft_strndup(to_dup,8));
    return (0);
}