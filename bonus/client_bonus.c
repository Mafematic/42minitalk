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

#include "serverclient_bonus.h"

void	send_char_as_signal(int pid, char c)
{
	int	ascii_value;
	int	i;

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

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	pid_t	client_pid;
	char	*string_to_send;

	if (argc != 3)
	{
		write(1, "Wrong amount of parameters", 26);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	string_to_send = argv[2];
	client_pid = getpid();
	print_pid_and_string(server_pid, string_to_send);
	if (setup_signals())
		return (1);
	send_pid_as_signal(server_pid, client_pid);
	send_signals(server_pid, string_to_send);
	sleep(1);
	return (0);
}
