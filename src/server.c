/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:26:03 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/01 01:19:29 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_list	*g_pidlist;
// se debe usar como global, ya que no se puede pasar argumentos al
// signal handler, la firma ya está definida.

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	t_list	*current;

	current = ft_lstnew((void *)info);
	ft_lstadd_back(&g_pidlist, current);
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

void	process_lst(int ppid)
{
	t_list		*lst;
	char		*buf;
	static int	i;
	t_list		*tmp;

	lst = g_pidlist;
	if (!lst)
		return ;
	ppid = ((siginfo_t *)(lst->content))->si_pid;
	while (lst)
	{
		if (ppid == ((siginfo_t *)(lst->content))->si_pid)
		{
			print_signal(((siginfo_t *)(lst->content))->si_signo, i, ppid);
			tmp = lst->next;
			ft_lst_deletenode(lst);
			lst = tmp;
		}
		else
			lst = lst->next;
		if (!lst)
		{
			i++;
			lst = g_pidlist;
			ppid = ((siginfo_t *)(lst->content))->si_pid;
		}
	}
}

int	main(void)
{
	t_sigaction	sa;
	sigset_t	set;

	g_pidlist = NULL;
	ft_printf("Server PID: %d\n", getpid());
	start_signal(&sa);
	while (1)
	{
		usleep(100000);
		stop_signals(&set);
		process_lst(0);
		sigprocmask(SIG_SETMASK, &set, NULL);
	}
	return (0);
}
