/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_managment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:35:23 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/19 11:02:03 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*find_exec(char **src, char *cmd)
{
	ft_strlcpy(*src, *src + 5, ft_strlen_chr(*src, '\0'));
	while (*src)
	{
		*src = ft_strconc(*src, ft_strdup("/"));
		*src = ft_strconc(*src, ft_strdup(cmd));
		if (!access(*src, 1))
			return (*src);
		src++;
	}
	return (NULL);
}

void	exec(char *cmd, char **envp)
{
	char	*path;
	char	**src;

	path = find_env_var(envp, "PATH");
	src = ft_split(path, ':');
	path = find_exec(src, cmd);
	if (path != NULL)
	{
		execve(path, NULL, envp);
		free(path);
	}
	free_char_sstar(src);
}
