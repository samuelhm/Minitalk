/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:28:01 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/01 21:25:03 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

//INCLUDES
# include "libft.h"
# include <signal.h>
# include <sys/types.h>
# include <limits.h>

# ifndef TIMEOUT
#  define TIMEOUT 1000000
# endif

typedef struct s_pidid
{
	int				pid;
	int				index;
}	t_pidid;

// VARS
typedef struct sigaction	t_sigaction;

void	print_signal(int sig);

#endif
