/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shurtado <shurtado@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 02:36:54 by shurtado          #+#    #+#             */
/*   Updated: 2024/08/31 02:46:08 by shurtado         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	new_pidid(t_pidid *pidid, siginfo_t *info)
{
	pidid = malloc(sizeof(t_pidid));
	if (!pidid)
		return (-1);
	pidid->pid = info->si_pid;
	pidid->index = ft_lstsize(g_pidlist);
	ft_lstadd_back(&g_pidlist, ft_lstnew(pidid));
	return (pidid->index);
}
