/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:27:18 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/30 18:41:26 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_message(int s_pid, char *str)
{
	int	i;
	int	bit;

	while (1)
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
			usleep(100);
		}
		if (*str == '\0')
			break ;
		str++;
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
	{
		ft_printf("Uso: ./clien {ServerPID} {\"Message\"}\n");
		return (-1);
	}
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
