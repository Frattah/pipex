/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:39:44 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/26 11:11:12 by frmonfre         ###   ########.fr       */
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
	ft_strlcpy(*src, *src + 5, ft_strlen(*src, '\0'));
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
	char	**args;

	args = ft_split(cmd, ' ');
	if (!isin(cmd, '/'))
	{
		path = find_env_var(envp, "PATH");
		src = ft_split(path, ':');
		path = find_exec(src, args[0]);
	}
	else
		path = args[0];
	if (path != NULL)
	{
		execve(path, args, envp);
		free(path);
	}
	free_char_sstar(src);
}
