/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:35:23 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/19 08:46:03 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*find_env_var(char **envp, char *var)
{
	if (var == NULL)
		return (NULL);
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
			return (*envp);
		envp++;
	}
	return (NULL);
}

char	*find_exec(char **src, char **argv)
{
	char	*out;

	while (*src)
	{
		out = ft_strconc(*src, ft_strdup("/"));
		out = ft_strconc(out, ft_strdup(argv[2]));
		if (!access(out, 1))
			break ;
		src++;
	}
	return (out);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	char	**src;
	char	*cnc;

	path = find_env_var(envp, "PATH");
	src = ft_split(path, ':');
	cnc = find_exec(src, argv);
	if (cnc != NULL)
		execve(cnc, argv + 2, envp);
}
