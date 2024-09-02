/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:27:18 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/02 01:05:25 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_received = 0;

void	handle_response(int sig)
{
	if (sig == SIGUSR1)
		g_received = 1;
}

static void	send_next_char(char *str, int s_pid)
{
	int	bit;
	int	i;
	int	timeout;

	i = 7;
	timeout = 0;
	g_received = 0;
	while (i >= 0)
	{
		bit = (*str >> i) & 1;
		if (bit == 1)
			kill(s_pid, SIGUSR1);
		else
			kill(s_pid, SIGUSR2);
		while (!g_received && timeout < TIMEOUT)
		{
			usleep(50);
			timeout += 50;
		}
		timeout = 0;
		if (!g_received)
			continue ;
		g_received = 0;
		i--;
	}
}

void	send_message(int s_pid, char *str)
{
	while (1)
	{
		send_next_char(str, s_pid);
		if (*str == '\0')
			break ;
		else
			str++;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;

	sa.sa_handler = handle_response;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (argc != 3)
	{
		ft_printf("Uso: ./clien {ServerPID} {\"Message\"}\n");
		return (-1);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
