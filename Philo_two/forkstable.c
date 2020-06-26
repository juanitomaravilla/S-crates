/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkstable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 18:08:37 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/05/18 18:25:11 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philotwo.h"

int	philosophers_eating(t_listtwo *philosopher)
{
	if (sem_wait(philosopher->main_mutex) != 0)
		return (1);
	philosopher->eat = 1;
	philosopher->final_eat = take_the_time();
	philosopher->limit = philosopher->final_eat + philosopher->status->dying;
	if (show_text(philosopher, TYPE_EAT))
		return (1);
	usleep(philosopher->status->eating * 850);
	philosopher->eat_count++;
	philosopher->eat = 0;
	if (sem_post(philosopher->main_mutex))
		return (1);
	if (sem_post(philosopher->main_eat))
		return (1);
	return (0);
}

int	run_forks(t_listtwo *philosopher)
{
	if (sem_wait(philosopher->status->main_forks))
		return (1);
	if (show_text(philosopher, TYPE_FORK))
		return (1);
	if (sem_wait(philosopher->status->main_forks))
		return (1);
	if (show_text(philosopher, TYPE_FORK))
		return (1);
	return (0);
}

int	remove_forks(t_listtwo *philosopher)
{
	if (show_text(philosopher, TYPE_SLEEP))
		return (1);
	if (sem_post(philosopher->status->main_forks))
		return (1);
	if (sem_post(philosopher->status->main_forks))
		return (1);
	usleep(philosopher->status->sleeping * 850);
	return (0);
}
