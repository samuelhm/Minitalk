/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:26:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/30 18:34:04 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int sig)
{
	static int				bitcount;
	static unsigned char	rechar;

	rechar <<= 1;
	if (sig == SIGUSR1)
		rechar |= 1;
	bitcount++;
	if (bitcount == 8)
	{
		if (rechar == '\0')
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(rechar, 1);
		bitcount = 0;
		rechar = 0;
	}
}

int	main(void)
{
	t_sigaction	sa;
	pid_t		pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_NODEFER;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
