/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 15:07:38 by fszendzi          #+#    #+#             */
/*   Updated: 2023/07/30 15:07:40 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverclient_bonus.h"

void	ack_handler(int signum)
{
	if (signum == SIGUSR1)
	{
		write(1, "Acknowledgement received\n", 25);
		exit(0);
	}
}

void	print_pid_and_string(pid_t server_pid, char *string_to_send)
{
	write(1, "Server PID: ", 12);
	ft_putnbr_fd(server_pid, 1);
	write(1, "\n", 1);
	write(1, "String: ", 8);
	ft_putstr_fd(string_to_send, 1);
	write(1, "\n", 1);
}

void	send_signals(pid_t server_pid, char *string_to_send)
{
	int	i;

	i = 0;
	while (string_to_send[i] != '\0')
	{
		send_char_as_signal(server_pid, string_to_send[i]);
		i++;
	}
	send_char_as_signal(server_pid, '\0');
}

void	send_pid_as_signal(pid_t server_pid, pid_t client_pid)
{
	char	*pid_str;
	int		i;

	pid_str = ft_itoa(client_pid);
	i = 0;
	while (pid_str[i] != '\0')
	{
		send_char_as_signal(server_pid, pid_str[i]);
		i++;
	}
	free(pid_str);
	send_char_as_signal(server_pid, '\0');
}

int	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		write(1, "Error setting up sigaction\n", 27);
		return (1);
	}
	return (0);
}
