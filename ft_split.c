/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:39:44 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/18 10:42:12 by frmonfre         ###   ########.fr       */
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

size_t	ft_strlen_chr(const char *s, char c)
{
	size_t	ln;

	ln = 0;
	while (s[ln] && s[ln] != c)
		ln++;
	return (ln);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen_chr(src, '\0'));
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
		len = ft_strlen_chr(s_cpy, c);
		*split = (char *) malloc(sizeof(char) * (len + 1));
		if (*split == NULL)
			return (NULL);
		ft_strlcpy(*split++, s_cpy, len + 1);
		s_cpy += len;
	}
	return (split - cntword(s, c));
}
