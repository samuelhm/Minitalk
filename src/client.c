/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:27:18 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/31 06:29:38 by shurtado         ###   ########.fr       */
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

	i = 7;
	while (i >= 0)
	{
		bit = (*str >> i) & 1;
		if (bit == 1)
			kill(s_pid, SIGUSR1);
		else
			kill(s_pid, SIGUSR2);
		i--;
		usleep(50);
	}
}

void	send_message(int s_pid, char *str)
{
	int	timeout;

	timeout = INT_MAX;
	while (1)
	{
		g_received = 0;
		send_next_char(str, s_pid);
		while (!g_received && timeout > 0)
		{
			usleep(1);
			timeout -= 1;
		}
		if (timeout <= 0 && g_received == 0)
			continue ;
		else if (*str == '\0')
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
