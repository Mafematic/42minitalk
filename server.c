#include "serverclient.h"

int main(void)
{
	// 1. Get Server ID.
	pid_t serverPID = getpid();
	
	printf("Server PID: %d\n", serverPID);

	return 0;
}