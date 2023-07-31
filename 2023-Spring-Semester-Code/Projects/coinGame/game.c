#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h> 
#include "run-game.c"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Usage: %s n p\n", argv[0]);
		return 0;
	}
	int n = atoi(argv[1]);
	double p = atof(argv[2]);
	assert(n>=1 && n <=10000);
	assert(p>=0.1 && p< 1.0);
	printf("%d %lf\n", n, p);
	run_simulation(n,p);
	return 0;
}