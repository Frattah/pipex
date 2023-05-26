/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmonfre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:17:43 by frmonfre          #+#    #+#             */
/*   Updated: 2023/05/26 11:49:21 by frmonfre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>	// open
# include <unistd.h>	// fork write pipe execve access close
# include <stdio.h>	// perror
# include <sys/wait.h>	// wait
# include <stdlib.h>	// malloc free
# include <stddef.h>	// size_t

typedef struct pipex_ist
{
	int		fdin;
	int		fdout;
	int		pipefd[2];
	int		tmp;
	int		ac;
	char	**en;
}	t_pipex_ist;

// -------- String utils -----------------

size_t		cntword(char const *s, char c);
char		*skpstr(char *s, char c);
int			isin(char *s, char c);
size_t		ft_strlen(const char *s, char c);
char		**ft_split(char const *s, char c);
// ---------------------------------------
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strconc(char *s1, char *s2);

// --------- Executor --------------------

char		*find_env_var(char **envp, char *var);
char		*find_exec(char **src, char *cmd);
void		exec(char *cmd, char **envp);

// --------- Initialization --------------

t_pipex_ist	*pipex_ist_init(int ac, char **av, char **en);
void		child_rout(t_pipex_ist *ist, char *cmd, int i);

// --------- Error handling --------------

void		short_err_mess(char *err);
void		free_char_sstar(char **src);
void		short_err_mess(char *err);

#endif
