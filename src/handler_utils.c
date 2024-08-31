/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:36:54 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/31 06:28:20 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	new_pidid(t_pidid **pidid, siginfo_t *info)
{
	(*pidid)->pid = info->si_pid;
	(*pidid)->index = ft_lstsize(g_pidlist);
	ft_lstadd_back(&g_pidlist, ft_lstnew(*pidid));
	return ((*pidid)->index);
}

void	print_signal(int sig, int index, int pid)
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
		kill(pid, SIGUSR1);
	}
}
