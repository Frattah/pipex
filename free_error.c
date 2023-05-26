/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 09:06:03 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/19 10:41:56 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_char_sstar(char **src)
{
	int	i;

	i = -1;
	while (src[++i])
	{
		free(src[i]);
	}
	free(src);
}

void	error_managment(int ac, char **av)
{
	if (ac < 5)
	{
		write(STDERR_FILENO, "Usage: ", 7);
		write(STDERR_FILENO, av[0], ft_strlen(av[0], '\0'));
		write(STDERR_FILENO, " infile cmd1 cmd2 ... outfile\n", 36);
		exit(1);
	}
	if (access(av[1], R_OK))
	{
		perror(av[1]);
		exit(1);
	}
}

void	short_err_mess(char *err)
{
	perror(err);
	exit(1);
}
