/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:39:44 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/26 09:30:56 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	cntword(char const *s, char c)
{
	size_t	i;
	size_t	w;

	i = 0;
	w = 0;
	if (s == NULL || *s == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] != c)
			i++;
		while (s[i] && s[i] == c)
		{
			if (i != 0 && s[i - 1] != c)
				w++;
			i++;
		}
	}
	if (s[i - 1] != '\0' && s[i - 1] != c)
		w++;
	return (w);
}

char	*skpstr(char *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

size_t	ft_strlen(const char *s, char c)
{
	size_t	ln;

	ln = 0;
	while (s[ln] && s[ln] != c)
		ln++;
	return (ln);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	words;
	char	*s_cpy;
	size_t	len;

	words = cntword(s, c);
	split = (char **) malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	s_cpy = (char *) s;
	split[words] = NULL;
	while (s != NULL && *s != 0 && words--)
	{
		s_cpy = skpstr(s_cpy, c);
		len = ft_strlen(s_cpy, c);
		*split = (char *) malloc(sizeof(char) * (len + 1));
		if (*split == NULL)
			return (NULL);
		ft_strlcpy(*split++, s_cpy, len + 1);
		s_cpy += len;
	}
	return (split - cntword(s, c));
}
