/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:28:01 by shurtado          #+#    #+#             */
/*   Updated: 2024/09/02 14:39:11 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

//INCLUDES
# include "libft.h"
# include <signal.h>
# include <sys/types.h>
# include <limits.h>

# ifndef TIMEOUT
#  define TIMEOUT 500
# endif
# ifndef MAX_CLIENT
#  define MAX_CLIENT 500
# endif
# ifndef AVAILABLE
#  define AVAILABLE 2147483647
# endif

typedef struct s_pidid
{
	int				pid;
	int				index;
}	t_pidid;

// VARS
typedef struct sigaction	t_sigaction;

#endif
