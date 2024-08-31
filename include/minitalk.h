/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:28:01 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/31 03:29:37 by shurtado         ###   ########.fr       */
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
#  define MAX_CLIENT 50
# endif

typedef struct s_pidid
{
	int				pid;
	int				index;
}	t_pidid;

extern t_list				*g_pidlist;
// VARS
typedef struct sigaction	t_sigaction;

int		new_pidid(t_pidid *pidid, siginfo_t *info);
void	print_signal(int sig, int index, int pid);

#endif
