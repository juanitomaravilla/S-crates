/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 17:56:45 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/20 19:19:28 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philotwo.h"

static void		*display_count(void *philosopher_status)
{
	t_list		*condition;
	int			i;

	condition = (t_list*)philosopher_status;
	while (condition->actual_eat < condition->times_to_eat)
	{
		i = 0;
		while (i < condition->total)
			if (sem_wait(condition->philosophers[i++].main_eat))
				return ((void*)0);
		condition->actual_eat++;
	}
	if (show_text(&condition->philosophers[0], TYPE_OVER))
		return ((void*)0);
	if (sem_post(condition->philospher_dead))
		return ((void*)0);
	return ((void*)0);
}

static void		*take_display(void *philosopher_status)
{
	t_listtwo		*philosopher;

	philosopher = (t_listtwo*)philosopher_status;
	while (1)
	{
		if (sem_wait(philosopher->main_mutex) != 0)
			return ((void*)0);
		if (!philosopher->eat && take_the_time() > philosopher->limit)
		{
			if (show_text(philosopher, TYPE_DIED))
				return ((void*)0);
			if (sem_post(philosopher->main_mutex))
				return ((void*)0);
			if (sem_post(philosopher->status->philospher_dead))
				return ((void*)0);
			return ((void*)0);
		}
		if (sem_post(philosopher->main_mutex))
			return ((void*)0);
	}
	return ((void*)0);
}

static void		*loop(void *philosopher_status)
{
	t_listtwo	*philosopher;
	pthread_t	tid;
	int			finish;

	philosopher = (t_listtwo*)philosopher_status;
	philosopher->final_eat = take_the_time();
	philosopher->limit = philosopher->final_eat + philosopher->status->dying;
	if (pthread_create(&tid, NULL, &take_display, philosopher_status) != 0)
		return ((void*)1);
	pthread_detach(tid);
	while (1)
	{
		if (run_forks(philosopher))
			return ((void*)0);
		finish = philosophers_eating(philosopher);
		if (remove_forks(philosopher))
			return ((void*)0);
		if (finish)
			return ((void*)0);
		if (show_text(philosopher, TYPE_THINK))
			return ((void*)0);
	}
	return ((void*)0);
}

static int		sons(t_list *condition)
{
	int			i;
	void		*philosopher;
	pthread_t	tid;

	if (condition->times_to_eat > 0)
	{
		if (pthread_create(&tid, NULL, &display_count, (void*)condition) != 0)
			return (1);
		pthread_detach(tid);
	}
	condition->start = take_the_time();
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

int			main(int argc, char const **argv)
{
	t_list	state;

	if (argc < 5 || argc > 6)
		return (print_error("error: bad arguments\n"));
	if (start(&state, argc, argv)
		|| sons(&state))
		return (clean_semaphore(&state) && print_error("error: fatal\n"));
	sem_wait(state.philospher_dead);
	clean_semaphore(&state);
	return (0);
}
