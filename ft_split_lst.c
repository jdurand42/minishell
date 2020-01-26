#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct    s_list
{
    void            *content;
    struct s_list    *next;
}                t_list;

t_list    *ft_lstnew(const void *content)
{
    t_list            *buffer;

    if (!(buffer = (t_list*)malloc(sizeof(t_list))))
        return (NULL);
    if (!content)
        content = NULL;
    else
        buffer->content = (void*)content;
    buffer->next = NULL;
    return (buffer);
}

void    ft_lstadd_back(t_list **alst, t_list *new)
{
    t_list    *buffer;

    if (alst == NULL)
        return ;
    buffer = *alst;
    if (new == NULL)
        return ;
    if (*alst == NULL)
    {
        *alst = new;
        return ;
    }
    while (buffer->next != NULL)
        buffer = buffer->next;
    buffer->next = new;
}


char    *ft_strndup(char const *src, size_t n)
{
    size_t    i;
    char    *dest;

    i = 0;
    if (!(dest = (char*)malloc((n + 1) * sizeof(char))))
        return (NULL);
    else
    {
        while (src[i] != '\0' && i < n)
        {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
        return (dest);
    }
}

int    ft_cmp_set(char c, int *flag)
{
    unsigned char    pc;
    int                i;

    i = 0;
    pc = (unsigned char)c;
    if (*flag == 0 && c == ' ')
      return (1);
  else if (c == 34 && *flag != 2)
  {
    *flag ^= 1;
    return (1);
  }
  else if (c == 39 && *flag != 1)
  {
    *flag ^= 2;
    return (1); // a verifier en vrai
  }
    i++;
    return (0);
}
int    count_words(char const *s, char *set)
{
    unsigned int    i;
    unsigned int    size;
    int             flag;
    i = 0;
    size = 0;
    flag = 0;
    while (s[i] != 0)
    {
        if (i > 0 && (ft_cmp_set(s[i], &flag)) && !(ft_cmp_set(s[i - 1], &flag)))
            size++;
        i++;
    }
    if (i > 0 && !(ft_cmp_set(s[i - 1], &flag)))
        size++;
    return (size);
}

t_list        *ft_strsplitlst(char const *s, char *set)
{
    unsigned int    i;
    unsigned int    st;
    t_list            *list;
    unsigned int    size;
  int           flag;
    i = 0;
    list = NULL;
    st = 0;
  flag = 0;
    size = count_words(s, set);
  flag = 0;
    while (size--)
    {
        while (s[i] != 0 && ft_cmp_set(s[i], &flag))
            i++;
        st = i;
        while (s[i] != 0 && !ft_cmp_set(s[i], &flag))
            i++;
        ft_lstadd_back(&list, ft_lstnew(ft_strndup(&s[st], i - st)));
    }
    return (list);
}

int main() {
  t_list *lst = ft_strsplitlst("echo lol 'non oui'", " ");
  t_list *b = lst;
  while (b != NULL)
  {
    printf("%s\n", (char*)b->content);
    b = b->next;
  }
  return 0;
}
