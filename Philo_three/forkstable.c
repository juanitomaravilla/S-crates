/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forkstable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 19:01:26 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/05/18 18:24:44 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philothree.h"

void	philosophers_eating(t_listtwo *philosopher)
{
	sem_wait(philosopher->main_mutex);
	philosopher->eat = 1;
	philosopher->final_eat = take_the_time();
	philosopher->limit = philosopher->final_eat + philosopher->status->dying;
	show_text(philosopher, TYPE_EAT);
	usleep(philosopher->status->eating * 850);
	philosopher->eat_count++;
	philosopher->eat = 0;
	sem_post(philosopher->main_mutex);
	sem_post(philosopher->main_eat);
}

void	run_forks(t_listtwo *philosopher)
{
	sem_wait(philosopher->status->main_forks);
	show_text(philosopher, TYPE_FORK);
	sem_wait(philosopher->status->main_forks);
	show_text(philosopher, TYPE_FORK);
}

void	remove_forks(t_listtwo *philosopher)
{
	show_text(philosopher, TYPE_SLEEP);
	sem_post(philosopher->status->main_forks);
	sem_post(philosopher->status->main_forks);
	usleep(philosopher->status->sleeping * 850);
}
