/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:35:23 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/22 10:02:30 by frmonfre         ###   ########.fr       */
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
	int		fdout;
	int		i;
	int		pipe_fd[2];
	int		pid;
	int		tmp;

	fdout = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	i = 0;
	tmp = dup(STDIN_FILENO);
	while (++i < argc - 1)
	{
		if (i != argc - 2)
			pipe(pipe_fd);
		pid = fork();
		if (!pid)
		{
			if (i == 1)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
			else if (i == argc - 2)
			{
				dup2(tmp, STDIN_FILENO);
				dup2(fdout, STDOUT_FILENO);
			}
			else
			{
				dup2(tmp, STDIN_FILENO);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
			close(tmp);
			exec(argv[i], envp);
		}
		if (i == argc - 2)
			waitpid(pid, NULL, 0);
		close(tmp);
		if (i != argc - 2)
		{
			tmp = dup(pipe_fd[0]);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
	}
	close(fdout);
}
