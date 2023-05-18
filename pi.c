#include "pipex.h"

void	child_one(int fd1, char *cmd1, int end[])
{
	dup2(fd1, 0);
	dup2(end[1], 1);
	printf("Sono il child1\n");
	close(end[0]);
	close(fd1);
	exit(0);
}

void	child_two(int fd2, char *cmd2, int end[])
{
	dup2(fd2, 1);
	dup2(end[0], 0);
	printf("Sono il child2\n");
	close(end[1]);
	close(fd2);
	exit(0);
}

void	pipex(int fd1, int fd2, int argc, char **envp)
{
	int	end[2];
	pid_t	child1;
	pid_t	child2;

	pipe(end);
	child1 = fork();
	if (child1 < 0)
		return (perror("Fork: "));
	if (child1 == 0)
		child_one(fd1, cmd1, end);
	child2 = fork();
	if (child2 < 0)
		return (perror("Fork: "));
	if (child2 == 0)
		child_two(fd2, cmd2, end);
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	fd1 = open(argv[0], O_RDONLY);
	fd2 = open(argv[argc - 1], O_CREAT | O_RDONLY | O_TRUNC);
	if (fd1 < 0 || fd2 < 0)
		return (-1);
	pipex(fd1, fd2, argc, envp);
	return (0);
}
