/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:51:46 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/19 09:56:57 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	isin(char c, char const *set)
{
	int	fnd;

	fnd = 0;
	while (*set && !fnd)
		if (*set++ == c)
			fnd = 1;
	return (fnd);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*out;

	if (s == NULL)
		return (NULL);
	if (len >= ft_strlen_chr(s, '\0'))
		len = ft_strlen_chr(s, '\0');
	if (start >= ft_strlen_chr(s, '\0'))
		len = 0;
	if (len > ft_strlen_chr(s, '\0'))
		len = ft_strlen_chr(s, '\0');
	out = (char *) malloc(sizeof(char) * (len + 1));
	if (out == NULL)
		return (NULL);
	if (start >= ft_strlen_chr(s, '\0'))
	{
		out[0] = 0;
		return (out);
	}
	i = start - 1;
	while (s[++i] && i < len + start)
		out[i - start] = s[i];
	out[i - start] = '\0';
	return (out);
}

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	i;
	size_t	j;
	char	*nw;

	i = 0;
	if (s == NULL || set == NULL)
		return (NULL);
	j = ft_strlen_chr(s, '\0') - 1;
	while (s[i] && isin(s[i], set))
		i++;
	while (i < j && isin(s[j], set))
		j--;
	nw = ft_substr(s, i, j - i + 1);
	return (nw);
}
