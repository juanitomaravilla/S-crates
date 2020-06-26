/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 18:56:53 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/21 19:53:15 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philothree.h"

int			clean_semaphore(t_list *p)
{
	int		i;
	char	semaphore[255];

	sem_unlink(SEMAPHORE_FORK);
	sem_unlink(SEMAPHORE_WRITE);
	sem_unlink(SEMAPHORE_DEAD);
	sem_unlink(SEMAPHORE_DEADW);
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

int			print_error(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
	return (1);
}

static int		loop(t_listtwo *philosopher_status)
{
	t_listtwo	*philosopher;
	pthread_t	tid;

	philosopher = (t_listtwo*)philosopher_status;
	philosopher->final_eat = take_the_time();
	philosopher->limit = philosopher->final_eat + philosopher->status->dying;
	if (pthread_create(&tid, NULL, &take_display, philosopher) != 0)
		return (1);
	pthread_detach(tid);
	while (1)
	{
		run_forks(philosopher);
		philosophers_eating(philosopher);
		remove_forks(philosopher);
		show_text(philosopher, TYPE_THINK);
	}
	return (0);
}

static int		init_process(t_list *p)
{
	int			i;
	void		*philosopher;

	p->start = take_the_time();
	i = 0;
	while (i < p->total)
	{
		philosopher = (void*)(&p->philosophers[i]);
		p->philosophers[i].pid = fork();
		if (p->philosophers[i].pid < 0)
			return (1);
		else if (p->philosophers[i].pid == 0)
		{
			loop(&p->philosophers[i]);
			exit(0);
		}
		usleep(100);
		i++;
	}
	return (0);
}

int			main(int argc, char const **argv)
{
	int		i;
	t_list	p;

	if (argc < 5 || argc > 6)
		return (print_error("error: bad arguments\n"));
	if (start(&p, argc, argv) || init_sons(&p)
		|| init_process(&p))
		return (clean_semaphore(&p) && print_error("error: fatal\n"));
	sem_wait(p.philosopher_dead);
	i = 0;
	while (i < p.total)
		kill(p.philosophers[i++].pid, SIGKILL);
	clean_semaphore(&p);
	return (0);
}
