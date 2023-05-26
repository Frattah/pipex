/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:35:23 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/26 10:42:36 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex_ist	*pipex_ist_init(int ac, char **av, char **en)
{
	t_pipex_ist	*ist;

	ist = (t_pipex_ist *) malloc(sizeof(t_pipex_ist));
	if (!ist)
		short_err_mess("malloc");
	if (!access(av[1], F_OK))
		ist->fdin = open(av[1], O_RDONLY);
	else
	{
		free(ist);
		short_err_mess("access");
	}
	ist->fdout = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (ist->fdin < 0 || ist->fdout < 0)
	{
		free(ist);
		short_err_mess("open");
	}
	ist->tmp = ist->fdin;
	ist->ac = ac;
	ist->en = en;
	return (ist);
}

void	child_rout(t_pipex_ist *ist, char *cmd, int i)
{
	char	**args;

	dup2(ist->tmp, STDIN_FILENO);
	if (i != ist->ac - 2)
		dup2(ist->pipefd[1], STDOUT_FILENO);
	else
		dup2(ist->fdout, STDOUT_FILENO);
	close(ist->fdout);
	close(ist->tmp);
	close(ist->pipefd[0]);
	close(ist->pipefd[1]);
	exec(cmd, ist->en);
	exit(1);
}

int	main(int ac, char **av, char **en)
{
	int			i;
	int			pid;
	t_pipex_ist	*ist;

	error_managment(ac, av);
	ist = pipex_ist_init(ac, av, en);
	i = 1;
	while (++i < ac - 1)
	{
		if (i != ac - 2 && pipe(ist->pipefd) < 0)
			short_err_mess("pipe");
		pid = fork();
		if (pid < 0)
			short_err_mess("fork");
		if (!pid)
			child_rout(ist, av[i], i);
		ist->tmp = dup(ist->pipefd[0]);
		close(ist->pipefd[0]);
		close(ist->pipefd[1]);
		wait(NULL);
	}
	close(ist->fdin);
	close(ist->fdout);
	free(ist);
}
