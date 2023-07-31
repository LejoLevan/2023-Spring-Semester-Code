#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h> 

//write an integer to a pipe
void write_int(int pd, int value)
{
	write(pd, &value, sizeof(int));
}
//read an integer from a pipe
//the function returns the number of bytes read
int read_int(int pd, int *value)
{
	return read(pd, value , sizeof(int));
}

double random_double() {
        return (double) rand() / RAND_MAX;
}

int coin_flip(double p)
{
	return random_double() < p;
}
	
void run_simulation(int n, double p)
{
        int pd1[2];
        //pipe creation
        if(pipe(pd1) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd2[2];
        //pipe creation
        if(pipe(pd2) < 0)
        {
                perror("Error.");
                exit(-1);
        }
        pid_t pid = fork();
        if(pid == 0)
        {
                //TODO
                //fill in code below
                close(pd2[1]); // write end for parent
                close(pd1[0]); // read end for parent
		//note this is player A
		
		
		srand(3100);

                int v;
		//TODO
		//complete the following line of code
                while(read_int(pd2[0], &v)!=0)
                {
			//TODO
			//fill in code below
            double coinFlip = coin_flip(p);
            write_int(pd1[1], coinFlip);
                
		}
		//TODO
		//fill in code below
        close(pd1[1]); //close child write end
        close(pd2[0]); // close child read end
        exit(0);
	
	}
	//TODO
	//fill in code below
    close(pd1[1]); // close child write end 
    close(pd2[0]); // close child read end

        int pd3[2];
        //pipe creation
        if(pipe(pd3) < 0)
        {
                perror("Error.");
                exit(-1);
        }

        int pd4[2];
        //pipe creation
        if(pipe(pd4) < 0)
        {
                perror("Error.");
                exit(-1);
        }
        pid_t pid1 = fork();
		
        if(pid1 == 0)
        {
		//TODO
        close(pd1[0]);//close read end (from previous child) for parent
        close(pd2[1]);//close write end (from previous child) for parent

		//fill in code below
            close(pd4[1]); // write end for parent
            close(pd3[0]); // read end for parent
		//note this is player B
		
		
		srand(3504);

                int v;
                //TODO
                //complete the following line of code
                while(read_int(pd4[0], &v)!=0)
                {
                        //TODO
                        //fill in code below
                        double coinFlip = coin_flip(p);
                        write_int(pd3[1], coinFlip);
                
		}

		//TODO
		//fill in code below
        close(pd3[1]); //close child write end
        close(pd4[0]); //close child read end
        exit(0);
	
	}

    close(pd3[1]); // close child write end
    close(pd4[0]); // close child read end

	int n1 = 0;
	int n2 = 0;
	int v1, v2;

        while(n1 + n2 < n)
        {
		//TODO
		//finish the follow lines of code
		write_int(pd2[1], 1);
		write_int(pd4[1], 1);
                read_int(pd1[0], &v1);
		read_int(pd3[0], &v2);
		if(v1) n1++;
		else
		{
			if(v2) n2++;
		}
        }
	printf("prob of A wins = %.3lf\n", (double)(n1)/(n1+n2));
	//TODO
	//fill in code below
    close(pd2[1]); //close parent write end
    close(pd4[1]); //close parent write end

    close(pd1[0]); //close child read end
    close(pd3[0]); //close child read end
}