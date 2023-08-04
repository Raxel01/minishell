#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct list{

    struct list *prev;
    char *data;
    int index;
    struct list *next;
} l_list;

l_list *init_head(l_list **node)
{
    *node = malloc(sizeof(l_list));
    (*node)->prev= NULL;
    (*node)->data = "Abdelali";
    (*node)->next= NULL;
    return (*node);
}

l_list *build_new_token_node(char *content, int index)
{
    l_list *token;

    token = malloc(sizeof(l_list));

    token->data = content;
    token->index = index;
    token->next = NULL;
    token->prev = NULL;

    return (token);
}

void    add_tokens_to_list(l_list **token, l_list *next_token)
{
    l_list *cursur;
    if (!(*token))
        (*token) = next_token;
    else
    {
        cursur = *token;
        while (cursur->next)
            cursur = cursur->next;
        cursur->next = next_token;
        next_token->prev = cursur;
    }
}

void    print_tokens(l_list **begin)
{
    l_list *cursur;

    cursur = (*begin);
    
    while (cursur)
    {
        if (cursur->index == 1)
           printf ("%p <-- %d --> %d\n",cursur->prev, cursur->index, cursur->next->index);
        else if (cursur->index == 10)
            printf ("%d <-- %d --> %p\n",cursur->prev->index, cursur->index, cursur->next);
        if (cursur->index != 1 && cursur->index != 10)
            printf ("%d <-- %d --> %d\n",cursur->prev->index, cursur->index, cursur->next->index);
            cursur = cursur->next;
    }
}
void leaks()
{
    system("leaks a.out");
}
int main ()
{
    // atexit(leaks);
    l_list *head;

    head = NULL;
    // init_head(&head);
    int i = 0;
    while (i <= 9)
    {
        add_tokens_to_list(&head,build_new_token_node("ls -la | wc -l | awk '{print $1}'", i));
        i++;
    }
    print_tokens(&head);
    return (0);
}