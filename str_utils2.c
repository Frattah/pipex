/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concatenate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 10:52:09 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/19 10:39:28 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	ln;
	size_t	i;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src, '\0'));
	ln = ft_strlen(dst, '\0');
	i = -1;
	if (dstsize == 0)
		return (ft_strlen(src, '\0'));
	if (ln < dstsize - 1 && dstsize > 0)
	{
		while (src[++i] && ln + i < dstsize - 1)
			dst[ln + i] = src[i];
		dst[ln + i] = '\0';
	}
	if (ln > dstsize)
		ln = dstsize;
	return (ln + ft_strlen(src, '\0'));
}

char	*ft_strdup(const char *s1)
{
	char	*nw;
	size_t	len;

	len = ft_strlen(s1, '\0') + 1;
	nw = (char *) malloc(sizeof(char) * len);
	if (nw == NULL)
		return (NULL);
	ft_strlcpy(nw, s1, len);
	return (nw);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
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
	return (ft_strlen(src, '\0'));
}

char	*ft_strconc(char *s1, char *s2)
{
	char	*nw;
	size_t	ln;

	ln = ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1;
	nw = (char *) malloc(sizeof(char) * ln);
	if (nw == NULL)
		return (NULL);
	ft_strlcat(nw, s1, ft_strlen(s1, '\0') + 1);
	ft_strlcat(nw, s2, ln);
	free(s1);
	free(s2);
	return (nw);
}
