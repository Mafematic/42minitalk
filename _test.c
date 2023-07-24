
// sigemptyset --> create empty signal set


/*
sigset_t mySignalSet;
// Initialize mySignalSet as an empty set
    if (sigemptyset(&mySignalSet) == -1) {
        perror("Error in sigemptyset");
        return 1;
*/

// sigaddset
// --> sigaddset(&mySignalSet, SIGINT) 
// Adds new set to mysignalset 


/*
struct sigaction {
    void (*sa_handler)(int);
    sigset_t sa_mask;
    int sa_flags;
};
*/

// 1. Start the server first

// 2. Print PID 

// 

// Signal verification

// Initialize mySignalSet as an empty set

	sigset_t mySignalSet;

	int sigemptyset(sigset_t *set);

    sigemptyset(&mySignalSet);

    // Add SIGINT (Interrupt signal) to the signal set
    if (sigaddset(&mySignalSet, SIGINT) == 0) {
        printf("SIGINT (Interrupt signal) is added to the signal set.\n");
    } else {
        perror("Error in sigaddset");
    }


void sigusr_handler(int signum, pid_t pid, char *str_to_send)
{
	if (signum != SIGUSR1 && signum != SIGUSR2)
	{
		write(1, "Not the correct signal\n", 23);
		return ;
	}
	else
	{
		int i = 0;
		while (str_to_send[i] != '\0')
		{
			send_char_as_signal(pid, str_to_send[i]);
			i++;
		}
	}
}