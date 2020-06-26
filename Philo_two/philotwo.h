/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philotwo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/20 18:00:34 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/21 19:33:44 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# define TYPE_EAT	0
# define TYPE_SLEEP	1
# define TYPE_FORK	2
# define TYPE_THINK	3
# define TYPE_DIED	4
# define TYPE_OVER	5

# define SEMAPHORE_FORK		"pSemaphoreFork"
# define SEMAPHORE_WRITE	"pSemaphoreWrite"
# define SEMAPHORE_DEAD		"pSemaphoreDead"
# define SEMAPHORE_PHILO	"pSemaphorePhilo"
# define SEMAPHORE_PHILOEAT	"pSemaphorePhiloEat"

struct s_list;

typedef struct		s_listtwo
{
	int				left_fork;
	int				right_fork;
	int				pos;
	uint64_t		limit;
	uint64_t		final_eat;
	int				eat;
	int				eat_count;
	struct s_list	*status;
	sem_t			*main_mutex;
	sem_t			*main_eat;
}					t_listtwo;

typedef struct		s_list
{
	int				total;
	int				times_to_eat;
	int				actual_eat;
	int				finished;
	uint64_t		start;
	uint64_t		dying;
	uint64_t		eating;
	uint64_t		sleeping;
	t_listtwo		*philosophers;
	sem_t			*main_forks;
	sem_t			*main_print;
	sem_t			*philospher_dead;
}					t_list;

int					main(int argc, char const **argv);

int					clean_semaphore(t_list *p);
int					print_error(char const *s);
int					show_text(t_listtwo *philosopher, int p);

int					start(t_list *p, int argc, char const **argv);
sem_t				*open_semaphore(char const *name, int i);
char				*pos_semaphore(char const *base, char *buff, int pos);

int					run_forks(t_listtwo *philosopher);
int					remove_forks(t_listtwo *philosopher);
int					philosophers_eating(t_listtwo *philosopher);

int					ft_strlen(char const *str);
int					ft_atoi(char const *str);
void				ft_putnbr_fd(uint64_t n, int fd);
int					ft_strcpy(char *dst, const char *src);
uint64_t			take_the_time(void);

#endif
