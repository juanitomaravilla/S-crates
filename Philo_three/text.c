/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:05:25 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/21 19:56:41 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philothree.h"

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

void		show_text(t_listtwo *philosopher, int p)
{
	sem_wait(philosopher->status->main_print);
	sem_wait(philosopher->status->print_dead);
	ft_putnbr_fd(take_the_time() - philosopher->status->start, 1);
	write(1, "\t", 1);
	if (p != TYPE_OVER)
		ft_putnbr_fd(philosopher->pos + 1, 1);
	write(1, take_text(p), ft_strlen(take_text(p)));
	if (p < TYPE_DIED)
		sem_post(philosopher->status->print_dead);
	sem_post(philosopher->status->main_print);
}

void		*display_count(void *philosopher_status)
{
	t_list *p;
	int		total;
	int		i;

	p = (t_list*)philosopher_status;
	total = 0;
	while (total < p->times_to_eat)
	{
		i = 0;
		while (i < p->total)
			sem_wait(p->philosophers[i++].main_eat);
		total++;
	}
	show_text(&p->philosophers[0], TYPE_OVER);
	sem_post(p->philosopher_dead);
	return ((void*)0);
}

void			*take_display(void *philosopher_status)
{
	t_listtwo		*philosopher;

	philosopher = (t_listtwo*)philosopher_status;
	while (1)
	{
		sem_wait(philosopher->main_mutex);
		if (!philosopher->eat && take_the_time() > philosopher->limit)
		{
			show_text(philosopher, TYPE_DIED);
			sem_post(philosopher->main_mutex);
			sem_post(philosopher->status->philosopher_dead);
			return ((void*)0);
		}
		sem_post(philosopher->main_mutex);
		usleep(1000);
	}
	return ((void*)0);
}

int				init_sons(t_list *p)
{
	pthread_t	tid;

	if (p->times_to_eat > 0)
	{
		if (pthread_create(&tid, NULL, &display_count, (void*)p) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}
