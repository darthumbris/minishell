/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: shoogenb <shoogenb@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/17 16:07:02 by shoogenb      #+#    #+#                 */
/*   Updated: 2022/03/01 16:14:46 by shoogenb      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_splits(const char *s, char c)
{
	int	i;
	int	splt_i;

	i = 0;
	splt_i = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			splt_i++;
			while (s[i] == c && s[i])
				i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		splt_i++;
	return (splt_i);
}

static void	ft_word(char **word, int *len, char c)
{
	int	i;

	i = 0;
	*word = *word + *len;
	*len = 0;
	while (**word && **word == c)
		(*word)++;
	while ((*word)[i])
	{
		if ((*word)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

static char	**ft_free(char **split, int i)
{
	while (i)
	{
		free(split[i]);
		i--;
	}
	free (split);
	return (NULL);
}

static char	**ft_split_while(char const *s, char c, char **split, int splts)
{
	char	*word;
	int		word_len;
	int		i;

	i = 0;
	word = (char *)s;
	word_len = 0;
	while (i < splts)
	{
		ft_word(&word, &word_len, c);
		if (i == splts && s[ft_strlen(s) - 1] == c && splts != 0)
			break ;
		split[i] = malloc(sizeof(char) * (word_len + 1));
		if (split[i] == NULL)
			return (ft_free(split, i));
		ft_strlcpy(split[i++], word, word_len + 1);
	}
	split[i] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		splts;

	if (s == NULL)
		return (NULL);
	if (*s != 0)
	{
		splts = ft_count_splits(s, c);
		split = malloc(sizeof(char *) * (splts + 1));
		if (split == NULL)
			return (NULL);
		split = ft_split_while(s, c, split, splts);
	}
	else
		split = ft_calloc(1, sizeof(char *));
	return (split);
}
