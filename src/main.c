#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <errno.h>

#define SAMPLE_RATE 48000

uint8_t tripleOscillator(int t, int f)
{
	// frequencies for each oscillator.
	// play around with them, it is fun.
	float f0 = f+2;
	float f1 = f*5/4;
	float f2 = f1*6/5;
	
	// oscillators
	float osc0 = (sin(t*2*M_PI/SAMPLE_RATE*f0));
	float osc1 = (sin(t*2*M_PI/SAMPLE_RATE*f1));
	float osc2 = (sin(t*2*M_PI/SAMPLE_RATE*f2));

	// this does the following:
	//	adds the oscillators together
	//	divides them by three, to make the resulting wave as if it were the size of a single oscilator
	//	shitfs the wave up by one, because otherwise it would have negative portions.
	//	multiplies it, so that it takes up the entirety of the available space.
	return (uint8_t)(127*((osc0+osc1+osc2)/3+1));
}

int main()
{
	const double C=220;

	// set up pipe between the parent and future child process.
	// fd[1] the parent STDOUT, and fd[0] is the childs STDIN
	int fd[2];
	pipe(fd);

	// start a child process
	pid_t pid = fork();

	if (pid == 0)
	{
		/*
		 * This is the child process, it is in charge of sending the sound from
		 * the parent process to aplay.
		 */

		// close the unused file descriptor
		close(fd[1]);

		// remap STDIN for this process to the pipe
		dup2(fd[0], 0);

		// args for the command
		char *argv[] = {"aplay", "-r 48", NULL};

		// execute the command
		int e = execvp(argv[0], argv);
		int err = errno;	
		// check for errors
		if (e == -1)
		{
			printf("the error is (child): %d \n", err);
			exit(EXIT_FAILURE);
		}

		// close the other half of pipe before exiting.
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		/*
		 * This is the parent process. It handles the generation of the sound.
		 */

		// close the unused fd for the parent process
		close(fd[0]);

		// remap STDOUT for the parent 
		dup2(fd[1], 1);

		// generate sound and put it into the remapped STDOUT
		for (int t=0;;t++)
			putchar(tripleOscillator(t,C));

		// close the pipe and exit.
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}

}
