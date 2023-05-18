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

char	*path_envp(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH", 4))
			return (*envp);
		envp++;
	}
	return (NULL);
}

char	*find_exec(char **src, char **argv)
{
	char	*out;
	while (*src)
	{
		out = ft_strconc(*src, ft_strdup("/"));
		out = ft_strconc(out, ft_strdup(argv[2]));
		if (!access(out, 1))
			break;
		src++;
	}
	return (out);
}

int	main(int argc, char **argv, char **envp)
{
	char	*path;
	char	**src;
	char	*cnc;
	pid_t	pid;

	pid = fork();
	path = path_envp(envp);
	src = ft_split(path, ':');
	cnc = find_exec(src, argv);
	if (pid == 0 && cnc != NULL)
		execve(cnc, argv + 2, envp);
	else
		wait(NULL);
}
