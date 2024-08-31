/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:36:54 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/01 00:58:33 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	stop_signals(sigset_t *oldset)
{
	sigset_t	block_set;

	sigemptyset(&block_set);
	sigaddset(&block_set, SIGUSR1);
	sigaddset(&block_set, SIGUSR2);
	sigprocmask(SIG_BLOCK, &block_set, oldset);
}

void	print_signal(int sig, int index, int pid)
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
			ft_printf("%s\n", str[index]);
			free(str);
			str = NULL;
		}
		else
			str = ft_charjoin(str, rechar);
		bitcount = 0;
		rechar = 0;
	}
}
