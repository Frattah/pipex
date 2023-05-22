/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 08:36:04 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/22 11:29:46 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>	// open
# include <unistd.h>	// fork pipe execve access
# include <stdio.h>	// perror
# include <sys/wait.h>	// waitpid
# include <stdlib.h>
# include <stddef.h>	// size_t

typedef struct pipex_ist
{
	int	fdin;
	int	fdout;
	int	pipe_fd[2];
	int	tmp;
	int	ac;
}	t_pipex_ist;

size_t		cntword(char const *s, char c);
char		*skpstr(char *s, char c);
size_t		ft_strlen_chr(const char *s, char c);
char		**ft_split(char const *s, char c);

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strconc(char *s1, char *s2);

char		*find_env_var(char **envp, char *var);
char		*find_exec(char **src, char *cmd);
void		exec(char *cmd, char **envp);

void		redir(t_pipex_ist *ist, int i);
t_pipex_ist	*pipex_ist_init(int ac, char **av);
int			launch(t_pipex_ist *ist, char **av, char **en);
int			main(int ac, char **av, char **en);

#endif
