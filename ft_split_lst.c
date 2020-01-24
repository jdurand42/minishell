#include "libft.h"

static int	ft_cmp_set(char c, int flag)
{
	unsigned char	pc;
	int				i;

	i = 0;
	pc = (unsigned char)c;
	if (flag == 0 && c == ' ')
	  return (1);
  else if (c == '"' && flag != 2)
    flag ^= 1;
    return (1);
  else if (c == ''' && flag != 1)
    flag ^= 2;
    return (1); // a verifier en vrai
	i++;
	return (0);
}

static int	count_words(char const *s, char *set)
{
	unsigned int	i;
	unsigned int	size;

	i = 0;
	size = 0;
	while (s[i] != 0)
	{
		if (i > 0 && (ft_cmp_set(s[i])) && !(ft_cmp_set(s[i - 1])))
			size++;
		i++;
	}
	if (i > 0 && !(ft_cmp_set(s[i - 1]))
		size++;
	return (size);
}

t_list		*ft_strsplitlst(char const *s)
{
	unsigned int	i;
	unsigned int	st;
	t_list			*list;
	unsigned int	size;
  int           flag;

	i = 0;
	list = NULL;
	st = 0;
  flag = 0;
	size = count_words(s, set);
  flag = 0;
	while (size--)
	{
		while (s[i] != 0 && ft_cmp_set(s[i])
			i++;
		st = i;
		while (s[i] != 0 && !ft_cmp_set(s[i])
			i++;
		ft_lstadd_back(&list, ft_lstnew(ft_strndup(&s[st], i - st)));
	}
	return (list);
}
