/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serverclient.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fszendzi <fszendzi@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 13:55:52 by fszendzi          #+#    #+#             */
/*   Updated: 2023/07/28 13:55:56 by fszendzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERCLIENT_BONUS_H
# define SERVERCLIENT_BONUS_H

# include "../Libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <sys/types.h>

# define BUFFER_SIZE 1024

typedef struct s_server_state
{
	int				bit_count;
	unsigned char	received_char;
	char			buffer[BUFFER_SIZE];
	int				buffer_index;
	pid_t			client_pid;
}	t_server_state;

void	ack_handler(int signum);
void	sigusr_handler(int signum);
void	send_char_as_signal(int pid, char c);
void	print_pid_and_string(pid_t server_pid, char *string_to_send);
void	send_signals(pid_t server_pid, char *string_to_send);
void	send_pid_as_signal(pid_t server_pid, pid_t client_pid);
int		setup_signals(void);

#endif
