/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:55:17 by fszendzi          #+#    #+#             */
/*   Updated: 2023/07/28 13:55:20 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serverclient.h"

void send_char_as_signal(int pid, char c)
{
	int ascii_value;
	int i;

	ascii_value = (int)c;
	i = 0;
	while (i < 8)
	{
		if (ascii_value & (1 << i)) 
			kill(pid, SIGUSR1); 
		else 
			kill(pid, SIGUSR2);
		i++;
		usleep(200);
	}
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		write(1, "Wrong amount of parameters", 26);
		return 1;
	}

	pid_t server_pid = ft_atoi(argv[1]);
	if (server_pid == 0)
	{
		write(1, "Wrong Server ID\n", 16);
		return 1;
	}
	else 
	{
		write(1, "Server PID: ", 12);
		ft_putnbr_fd(server_pid, 1);
		write(1, "\n", 1);
	}

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