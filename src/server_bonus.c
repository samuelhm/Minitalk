/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:26:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/02 14:39:31 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	reset_values(char **buffer, int *bcount, unsigned char *rechar)
{
	*bcount = 0;
	*rechar = 0;
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
}

static int	print_signal(int sig, int index, int pid)
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
			reset_values(&str[index], &bitcount[index], &rechar[index]);
			return (AVAILABLE);
		}
		else
			str[index] = ft_charjoin(str[index], rechar[index]);
		bitcount[index] = 0;
		rechar[index] = 0;
	}
	return (pid);
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	index[MAX_CLIENT];
	int			i;

	(void)context;
	i = -1;
	while (index[++i] > 0)
	{
		if (index[i] == AVAILABLE)
			continue ;
		if (info->si_pid == index[i])
		{
			index[i] = print_signal(sig, i, info->si_pid);
			kill(info->si_pid, SIGUSR1);
			return ;
		}
	}
	i = 0;
	while (index[i] != 0 && index[i] != AVAILABLE)
		i++;
	if (i >= MAX_CLIENT)
		return ;
	index[i] = info->si_pid;
	index[i] = print_signal(sig, i, info->si_pid);
	kill(info->si_pid, SIGUSR1);
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

	ft_printf("Server PID: %d\n", getpid());
	start_signal(&sa);
	while (1)
	{
		pause();
	}
	return (0);
}
