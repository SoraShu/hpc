#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int glob = 6;
int main()
{
	pid_t pid;
	int x = 1;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: ");
	}
	else if (pid == 0)
	{
		glob = glob + 2;
		x = x + 2;
		sleep(10);
		printf("child : glob=%d, x=%d\n", glob, x);
	}
	else
	{
		glob = glob + 1;
		x = x + 1;
		sleep(10);
		printf("parent: glob=%d, x=%d\n", glob, x);
	}
}
