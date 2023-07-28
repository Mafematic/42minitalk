/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:55:28 by fszendzi          #+#    #+#             */
/*   Updated: 2023/07/28 13:55:30 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
        if (received_char == '\0')
		{
			ft_putstr_fd(buffer, 1);
			write(1, "\n", 1);
			buffer_index = 0;
		}
		bit_count = 0;
	}
}

int main(void)
{
	pid_t serverPID = getpid();
	
	write(1, "Server PID ", 11);
	ft_putnbr_fd(serverPID, 1);
	write(1, "\n", 1);

	struct sigaction sa;
    sa.sa_handler = sigusr_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

	 if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        write(1, "Error setting up sigaction\n", 27);
        return 1;
    }

	while (1)
    {
        sleep(1);
    }

	return 0;
}
