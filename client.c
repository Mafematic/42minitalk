#include "serverclient.h"

void send_char_as_signal(int pid, char c)
{
	int ascii_value = (int)c;

	for (int i = 0; i < 8; i++)
	{
		if (ascii_value & (1 << i)) 
			kill(pid, SIGUSR1); 
		else 
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "Wrong amount of parameters", 26);
		return 1;
	}

	// First Argument
	pid_t server_pid = ft_atoi(argv[1]);
	if (server_pid == 0)
	{
		printf("Wrong Server ID\n");
		return 1;
	}
	else 
	{
		printf("Server PID: %d\n", server_pid);
	}

	// Second Argument
	char *string_to_send = argv[2];
	printf("String: %s\n", string_to_send);

	int i = 0;
	while (string_to_send[i] != '\0')
	{
		send_char_as_signal(server_pid, string_to_send[i]);
		i++;
	}
	send_char_as_signal(server_pid, '\0');

	return 0;
}

