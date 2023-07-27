#include "serverclient.h"

#define BUFFER_SIZE 1024

void sigusr_handler(int signum)
{
	static int bit_count = 0;
	static unsigned char received_char;
	static char buffer[BUFFER_SIZE];
    static int buffer_index = 0;

	if (signum != SIGUSR1 && signum != SIGUSR2)
	{
		write(1, "Not the correct signal\n", 23);
		return ;
	}

	if (bit_count == 0)
		{
			received_char = 0;
		}

	if (bit_count < 8)
	{
		if (signum == SIGUSR1)
		{
			received_char = received_char | (1 << bit_count);
		}
		bit_count++;
	}
	if (bit_count == 8)
	{
		buffer[buffer_index++] = received_char;
		//printf("Received character: %c\n", received_char);
        if (received_char == '\0')
		{
			printf("Received string: %s\n", buffer);

			buffer_index = 0;
		}
		
		bit_count = 0;
	}
}

int main(void)
{
	// 1. Get Server ID.
	pid_t serverPID = getpid();
	
	printf("Server PID: %d\n", serverPID);

	struct sigaction sa;
    sa.sa_handler = sigusr_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

	 if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        perror("Error setting up sigaction");
        return 1;
    }

	while (1)
    {
        // The server will keep receiving signals and processing them in the signal handler.
        sleep(1); // Sleep to avoid busy-waiting, you can use more efficient synchronization mechanisms in practice.
    }

	return 0;
}