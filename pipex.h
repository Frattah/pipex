#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>	// open
# include <unistd.h>	// fork pipe execve access
# include <stdio.h>	// perror
# include <sys/wait.h>	// waitpid
# include <stdlib.h>
# include <stddef.h>	// size_t


size_t	cntword(char const *s, char c);
char	*skpstr(char *s, char c);
size_t	ft_strlen_chr(const char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	**ft_split(char const *s, char c);

char	*ft_strconc(char *s1, char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

#endif
