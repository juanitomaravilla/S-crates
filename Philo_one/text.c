/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 01:45:14 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/20 19:29:01 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philone.h"

static char	*take_text(int p)
{
	if (p == TYPE_EAT)
		return (" eat\n");
	else if (p == TYPE_SLEEP)
		return (" sleep\n");
	else if (p == TYPE_FORK)
		return (" take a fork\n");
	else if (p == TYPE_THINK)
		return (" think\n");
	else if (p == TYPE_OVER)
		return (" have already eaten the maximum quantity\n");
	return (" died\n");
}

void	show_text(t_listtwo *philosopher, int i)
{
	static int	ok = 0;

	pthread_mutex_lock(&philosopher->status->main_print);
	if (!ok)
	{
		ft_putnbr_fd(take_the_time() - philosopher->status->start, 1);
		write(1, "\t", 1);
		if (i != TYPE_OVER)
			ft_putnbr_fd(philosopher->pos + 1, 1);
		if (i >= TYPE_DIED)
			ok = 1;
		write(1, take_text(i), ft_strlen(take_text(i)));
	}
	pthread_mutex_unlock(&philosopher->status->main_print);
}
