/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:26:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/31 03:59:53 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_list	*g_pidlist;
// se debe usar como global, ya que no se puede pasar argumentos al
// signal handler, la firma ya está definida.

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	t_pidid	*pidid;
	t_list	*current;
	int		index;

	(void)context;
	current = g_pidlist;
	while (current)
	{
		pidid = (t_pidid *)current->content;
		if (pidid->pid == info->si_pid)
		{
			index = pidid->index;
			break ;
		}
		current = current->next;
	}
	if (!current)
		index = new_pidid(pidid, info);
	print_signal(sig, index, info->si_pid);
}

int	main(void)
{
	t_sigaction	sa;
	pid_t		pid;

	g_pidlist = NULL;
	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
