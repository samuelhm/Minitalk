/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:26:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/31 02:51:16 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_list	*g_pidlist;
// se debe usar como global, ya que no se puede pasar argumentos al
// signal handler, la firma ya está definida.

static void	print_signal(int sig, int index)
{
	static int				bitcount[MAX_CLIENT];
	static unsigned char	rechar[MAX_CLIENT];
	static char				*str[MAX_CLIENT];

	if (!str[index])
		str[index] = ft_calloc(sizeof(char), 1);
	rechar[index] <<= 1;
	if (sig == SIGUSR1)
		rechar[index] |= 1;
	bitcount[index]++;
	if (bitcount[index] == 8)
	{
		if (rechar[index] == '\0')
		{
			ft_printf("%s\n", str[index]);
			free(str[index]);
			str[index] = NULL;
		}
		else
			str[index] = ft_charjoin(str[index], rechar[index]);
		bitcount[index] = 0;
		rechar[index] = 0;
	}
}

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
	print_signal(sig, index);
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
