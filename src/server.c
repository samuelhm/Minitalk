/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:26:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/01 21:37:28 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int	g_actualpid;
// se debe usar como global, ya que no se puede pasar argumentos al
// signal handler, la firma ya está definida.

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (g_actualpid == 0)
		g_actualpid = info->si_pid;
	if (info->si_pid == g_actualpid)
	{
		print_signal(sig);
		kill(info->si_pid, SIGUSR1);
	}
}

void	print_signal(int sig)
{
	static int				bitcount;
	static unsigned char	rechar;
	static char				*str;

	if (!str)
		str = ft_calloc(sizeof(char), 1);
	rechar <<= 1;
	if (sig == SIGUSR1)
		rechar |= 1;
	bitcount++;
	if (bitcount == 8)
	{
		if (rechar == '\0')
		{
			ft_printf("%s\n", str);
			free(str);
			str = NULL;
			g_actualpid = 0;
		}
		else
			str = ft_charjoin(str, rechar);
		bitcount = 0;
		rechar = 0;
	}
}

static void	start_signal(t_sigaction *sa)
{
	sa->sa_sigaction = signal_handler;
	sa->sa_flags = SA_SIGINFO;
	sigemptyset(&sa->sa_mask);
	sigaction(SIGUSR1, sa, NULL);
	sigaction(SIGUSR2, sa, NULL);
}

int	main(void)
{
	t_sigaction		sa;

	g_actualpid = 0;
	ft_printf("Server PID: %d\n", getpid());
	start_signal(&sa);
	while (1)
	{
		pause();
	}
	return (0);
}
