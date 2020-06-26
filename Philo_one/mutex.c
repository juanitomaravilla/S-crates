/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 00:18:28 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/21 19:25:22 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philone.h"

static int	start_mutex(t_list *p)
{
	int		i;

	pthread_mutex_init(&p->main_print, NULL);
	pthread_mutex_init(&p->philosopher_dead, NULL);
	pthread_mutex_lock(&p->philosopher_dead);
	if (!(p->main_forks =
		(pthread_mutex_t*)malloc(sizeof(*(p->main_forks)) * p->total)))
		return (1);
	i = 0;
	while (i < p->total)
		pthread_mutex_init(&p->main_forks[i++], NULL);
	return (0);
}

static void	start_philosopher(t_list *p)
{
	int		i;

	i = 0;
	while (i < p->total)
	{
		p->philosophers[i].eat = 0;
		p->philosophers[i].pos = i;
		p->philosophers[i].left_fork = i;
		p->philosophers[i].right_fork = (i + 1) % p->total;
		p->philosophers[i].eat_count = 0;
		p->philosophers[i].status = p;
		pthread_mutex_init(&p->philosophers[i].main_mutex, NULL);
		pthread_mutex_init(&p->philosophers[i].main_eat, NULL);
		pthread_mutex_lock(&p->philosophers[i].main_eat);
		i++;
	}
}

int		start(t_list *p, int argc, char const **argv)
{
	p->total = ft_atoi(argv[1]);
	p->dying = ft_atoi(argv[2]);
	p->eating = ft_atoi(argv[3]);
	p->sleeping = ft_atoi(argv[4]);
	if (argc == 6)
		p->times_to_eat = ft_atoi(argv[5]);
	else
		p->times_to_eat = 0;
	if (p->total < 2 || p->total > 200 || p->dying < 60
		|| p->eating < 60 || p->sleeping < 60
		|| p->times_to_eat < 0)
		return (1);
	p->main_forks = NULL;
	p->philosophers = NULL;
	if (!(p->philosophers =
		(t_listtwo*)malloc(sizeof(*(p->philosophers)) * p->total)))
		return (1);
	start_philosopher(p);
	return (start_mutex(p));
}

int		clean_semaphore(t_list *condition)
{
	int	i;

	if (condition->main_forks)
	{
		i = 0;
		while (i < condition->total)
			pthread_mutex_destroy(&condition->main_forks[i++]);
		free(condition->main_forks);
	}
	if (condition->philosophers)
	{
		i = 0;
		while (i < condition->total)
		{
			pthread_mutex_destroy(&condition->philosophers[i].main_mutex);
			pthread_mutex_destroy(&condition->philosophers[i++].main_eat);
		}
		free(condition->philosophers);
	}
	pthread_mutex_destroy(&condition->main_print);
	pthread_mutex_destroy(&condition->philosopher_dead);
	return (1);
}

int		print_error(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
	return (1);
}
