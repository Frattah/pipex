/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:35:23 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/19 10:42:30 by frmonfre         ###   ########.fr       */
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
	ft_strlcpy(*src, *src + 5, ft_strlen_chr(*src, '\0'));
	while (*src)
	{
		*src = ft_strconc(*src, ft_strdup("/"));
		*src = ft_strconc(*src, ft_strdup(argv[2]));
		if (!access(*src, 1))
			return (*src);
		src++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	char	**src;
	int		fd1;
	int		fd2;

	path = find_env_var(envp, "PATH");
	src = ft_split(path, ':');
	path = find_exec(src, argv);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_WRONLY, O_TRUNC, O_CREAT);
	argv[3] = NULL;
	if (path != NULL)
	{
		execve(path, argv + 2, envp);
		free(path);
	}
	free_char_sstar(src);
	close(fd1);
	close(fd2);
}
