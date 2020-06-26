/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 18:12:29 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/21 19:42:49 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philotwo.h"

int				clean_semaphore(t_list *p)
{
	int			i;
	char		semaphore[255];

	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	if (p->philosophers)
	{
		i = 0;
		while (i < p->total)
		{
			pos_semaphore(SEMAPHORE_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			pos_semaphore(SEMAPHORE_PHILOEAT, (char*)semaphore, i++);
			sem_unlink(semaphore);
		}
		free(p->philosophers);
	}
	return (1);
}

int				print_error(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
	return (1);
}

static char		*take_text(int p)
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

int				show_text(t_listtwo *philosopher, int i)
{
	int			rest;
	static int	ok = 0;

	if (sem_wait(philosopher->status->main_print) != 0)
		return (1);
	rest = 1;
	if (!ok)
	{
		ft_putnbr_fd(take_the_time() - philosopher->status->start, 1);
		write(1, "\t", 1);
		if (i != TYPE_OVER)
			ft_putnbr_fd(philosopher->pos + 1, 1);
		if (i >= TYPE_DIED)
			ok = 1;
		write(1, take_text(i), ft_strlen(take_text(i)));
		rest = 0;
	}
	if (sem_post(philosopher->status->main_print))
		return (1);
	return (rest);
}
