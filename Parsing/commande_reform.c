#include "../Header/header.h"

int word_epur_helper(char *commande)
{
        int word;
        int i;

        i = 0;
        word = 0;
        while (commande[i])
        {
                if (((commande[i] != ' ' && commande[i] != '\t') && (commande[i+1] == ' ' || commande[i+1] == '\t')) ||\
                         ((commande[i] != ' ' && commande[i] != '\t') && commande[i + 1] == '\0'))
                        word++;
                i++;
        }
return (word);
}

int epur_len_helper(char *commande)
{
        int i;
        int not_whitspace;
        
        i = 0;
        not_whitspace = 0;
        while (commande[i])
        {
                if (commande[i] != ' ' && commande[i] != '\t')
                        not_whitspace++;
                i++;
        }
        return (not_whitspace);
}

char *epur_string(char *commande)
{
        if (commande && commande[0])
        {
        int i;
        int flg = 0;
        char *epured_string;
        char *begin;

        epured_string = malloc(sizeof(char) * (epur_len_helper(commande) + (word_epur_helper(commande) -1) + 1));
        begin = epured_string;
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
        return ("");
}