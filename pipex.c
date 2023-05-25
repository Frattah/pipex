/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:35:23 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/22 11:11:38 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redir(t_pipex_ist *ist, int i)
{
	if (i == 1)
	{
		dup2(ist->pipe_fd[1], STDOUT_FILENO);
		close(ist->pipe_fd[1]);
		close(ist->pipe_fd[0]);
	}
	else if (i == ist->ac - 2)
	{
		dup2(ist->tmp, STDIN_FILENO);
		dup2(ist->fdout, STDOUT_FILENO);
	}
	else
	{
		dup2(ist->tmp, STDIN_FILENO);
		dup2(ist->pipe_fd[1], STDOUT_FILENO);
		close(ist->pipe_fd[1]);
		close(ist->pipe_fd[0]);
	}
}

t_pipex_ist	*pipex_ist_init(int ac, char **av)
{
	t_pipex_ist	*ist;

	ist = (t_pipex_ist *) malloc(sizeof(t_pipex_ist));
	if (!ist)
		exit(1);
	ist->fdout = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	ist->tmp = dup(STDIN_FILENO);
	ist->ac = ac;
	ist->fdin = -1;
}

int	launch(t_pipex_ist *ist, char **av, char **en)
{
	int	pid;
	int	i;

	i = 0;
	while (++i < ist->ac - 1)
	{
		if (i != ist->ac - 2)
			pipe(ist->pipe_fd);
		pid = fork();
		if (!pid)
		{
			redir(ist, i);
			close(ist->tmp);
			exec(av[i], en);
		}
		if (i == ist->ac - 2)
			waitpid(pid, NULL, 0);
		close(ist->tmp);
		if (i != ist->ac - 2)
		{
			ist->tmp = dup(ist->pipe_fd[0]);
			close(ist->pipe_fd[0]);
			close(ist->pipe_fd[1]);
		}
	}
}

int	main(int ac, char **av, char **en)
{
	int			i;
	int			pid;
	t_pipex_ist	*ist;

	if (ac < 4)
	{
		write(STDERR_FILENO, "Usage: ", 7);
		write(STDERR_FILENO, av[0], ft_strlen_chr(av[0], '\0'));
		write(STDERR_FILENO, " cmd1 cmd2 outfile\n", 19);
		exit(1);
	}
	ist = pipex_ist_init(ac, av);
	launch(ist, av, en);
	close(ist->fdout);
	free(ist);
}
