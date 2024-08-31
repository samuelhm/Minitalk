/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:28:01 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/01 00:58:33 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

//INCLUDES
# include "libft.h"
# include <signal.h>
# include <sys/types.h>
# include <limits.h>

# ifndef MAX_CLIENT
#  define MAX_CLIENT 500
# endif

typedef struct s_pidid
{
	int				pid;
	int				index;
}	t_pidid;

extern t_list				*g_pidlist;
// VARS
typedef struct sigaction	t_sigaction;

void	stop_signals(sigset_t *oldset);
void	print_signal(int sig, int index, int pid);

#endif
