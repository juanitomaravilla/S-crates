/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 00:04:01 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/21 19:25:22 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philone.h"

static void		*display_count(void *philosopher_status)
{
	t_list		*condition;
	int			i;
	int			total;

	condition = (t_list*)philosopher_status;
	total = 0;
	while (total < condition->times_to_eat)
	{
		i = 0;
		while (i < condition->total)
			pthread_mutex_lock(&condition->philosophers[i++].main_eat);
		total++;
	}
	show_text(&condition->philosophers[0], TYPE_OVER);
	pthread_mutex_unlock(&condition->philosopher_dead);
	return ((void*)0);
}

static void		*take_display(void *philosopher_status)
{
	t_listtwo		*philosopher;

	philosopher = (t_listtwo*)philosopher_status;
	while (1)
	{
		pthread_mutex_lock(&philosopher->main_mutex);
		if (!philosopher->eat && take_the_time() > philosopher->limit)
		{
			show_text(philosopher, TYPE_DIED);
			pthread_mutex_unlock(&philosopher->main_mutex);
			pthread_mutex_unlock(&philosopher->status->philosopher_dead);
			return ((void*)0);
		}
		pthread_mutex_unlock(&philosopher->main_mutex);
		usleep(1000);
	}
}

static void		*loop(void *philosopher_status)
{
	t_listtwo	*philosopher;
	pthread_t	tid;

	philosopher = (t_listtwo*)philosopher_status;
	philosopher->final_eat = take_the_time();
	philosopher->limit = philosopher->final_eat + philosopher->status->dying;
	if (pthread_create(&tid, NULL, &take_display, philosopher_status) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		run_forks(philosopher);
		philosophers_eating(philosopher);
		remove_forks(philosopher);
		show_text(philosopher, TYPE_THINK);
	}
	return ((void*)0);
}

static int		sons(t_list *condition)
{
	int			i;
	void		*philosopher;
	pthread_t	tid;

	condition->start = take_the_time();
	if (condition->times_to_eat > 0)
	{
		if (pthread_create(&tid, NULL, &display_count, (void*)condition) != 0)
			return (1);
		pthread_detach(tid);
	}
	i = 0;
	while (i < condition->total)
	{
		philosopher = (void*)(&condition->philosophers[i]);
		if (pthread_create(&tid, NULL, &loop, philosopher) != 0)
			return (1);
		pthread_detach(tid);
		usleep(100);
		i++;
	}
	return (0);
}

int				main(int argc, char const **argv)
{
	t_list		p;

	if (argc < 5 || argc > 6)
		return (print_error("error: bad arguments\n"));
	if (start(&p, argc, argv))
		return (clean_semaphore(&p) && print_error("error: fatal\n"));
	if (sons(&p))
		return (clean_semaphore(&p) && print_error("error: fatal\n"));
	pthread_mutex_lock(&p.philosopher_dead);
	pthread_mutex_unlock(&p.philosopher_dead);
	clean_semaphore(&p);
	return (0);
}
