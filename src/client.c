/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:27:18 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/31 04:04:36 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t received = 0;

void	handle_response(int sig)
{
	if (sig == SIGUSR1)
		received = 1;
}

void	send_message(int s_pid, char *str)
{
	int	i;
	int	bit;

	while (1)
	{
		received = 0;
		while (!received)
		{
			i = 7;
			while (i >= 0)
			{
				bit = (*str >> i) & 1;
				if (bit == 1)
					kill(s_pid, SIGUSR1);
				else
					kill(s_pid, SIGUSR2);
				i--;
				usleep(200);
			}
			usleep(200);
		}
		if (*str == '\0')
			break ;
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
