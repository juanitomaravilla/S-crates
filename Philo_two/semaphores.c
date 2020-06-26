/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 18:05:33 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/20 20:18:48 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philotwo.h"

sem_t	*open_semaphore(char const *name, int i)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT | O_EXCL, 0644, i));
}

char	*pos_semaphore(char const *base, char *buff, int pos)
{
	int	i;

	i = ft_strcpy(buff, base);
	while (pos > 0)
	{
		buff[i++] = (pos % 10) + '0';
		pos /= 10;
	}
	buff[i] = 0;
	return (buff);
}

static int	start_semaphores(t_list *state)
{
	if ((state->main_forks = open_semaphore(SEMAPHORE_FORK, state->total)) < 0
		|| (state->main_print = open_semaphore(SEMAPHORE_WRITE, 1)) < 0
		|| (state->philospher_dead = open_semaphore(SEMAPHORE_DEAD, 0)) < 0)
		return (1);
	return (0);
}

static int	start_philosophers(t_list *p)
{
	int		i;
	char	semaphore[250];

	i = 0;
	while (i < p->total)
	{
		p->philosophers[i].eat = 0;
		p->philosophers[i].pos = i;
		p->philosophers[i].left_fork = i;
		p->philosophers[i].right_fork = (i + 1) % p->total;
		p->philosophers[i].eat_count = 0;
		p->philosophers[i].status = p;
		pos_semaphore(SEMAPHORE_PHILO, (char*)semaphore, i);
		if ((p->philosophers[i].main_mutex = open_semaphore(semaphore, 1)) < 0)
			return (1);
		pos_semaphore(SEMAPHORE_PHILOEAT, (char*)semaphore, i);
		if ((p->philosophers[i].main_eat = open_semaphore(semaphore, 0)) < 0)
			return (1);
		i++;
	}
	return (0);
}

int			start(t_list *p, int argc, char const **argv)
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
	p->actual_eat = 0;
	if (!(p->philosophers =
		(t_listtwo*)malloc(sizeof(*(p->philosophers)) * p->total)))
		return (1);
	if (start_philosophers(p))
		return (1);
	return (start_semaphores(p));
}
