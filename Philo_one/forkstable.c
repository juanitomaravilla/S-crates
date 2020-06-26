#/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   father.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 01:02:50 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/16 01:02:50 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philone.h"

void	run_forks(t_listtwo *philosopher)
{
	pthread_mutex_lock(&philosopher->status->main_forks[philosopher->left_fork]);
	show_text(philosopher, TYPE_FORK);
	pthread_mutex_lock(&philosopher->status->main_forks[philosopher->right_fork]);
	show_text(philosopher, TYPE_FORK);
}

void	remove_forks(t_listtwo *philosopher)
{
	show_text(philosopher, TYPE_SLEEP);
	pthread_mutex_unlock(&philosopher->status->main_forks[philosopher->left_fork]);
	pthread_mutex_unlock(&philosopher->status->main_forks[philosopher->right_fork]);
	usleep(philosopher->status->sleeping * 850);
}

void	philosophers_eating(t_listtwo *philosopher)
{
	pthread_mutex_lock(&philosopher->main_mutex);
	philosopher->eat = 1;
	philosopher->final_eat = take_the_time();
	philosopher->limit = philosopher->final_eat + philosopher->status->dying;
	show_text(philosopher, TYPE_EAT);
	usleep(philosopher->status->eating * 850);
	philosopher->eat_count++;
	philosopher->eat = 0;
	pthread_mutex_unlock(&philosopher->main_mutex);
	pthread_mutex_unlock(&philosopher->main_eat);
}
