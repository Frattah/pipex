/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:35:23 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/19 11:04:15 by frmonfre         ###   ########.fr       */
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
