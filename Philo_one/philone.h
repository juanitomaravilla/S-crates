/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philone.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 00:06:00 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/21 19:25:22 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILONE_H
# define PHILONE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <strings.h>
# include <stdarg.h>
# include <pthread.h>
# include <sys/time.h>

# define TYPE_EAT	0
# define TYPE_SLEEP	1
# define TYPE_FORK	2
# define TYPE_THINK	3
# define TYPE_DIED	4
# define TYPE_OVER	5


struct s_list;

typedef struct		s_listtwo
{
	int				right_fork;
	int				left_fork;
	int				pos;
	uint64_t		limit;
	uint64_t		final_eat;
	int				eat;
	int				eat_count;
	struct s_list	*status;
	pthread_mutex_t	main_mutex;
	pthread_mutex_t	main_eat;
}					t_listtwo;

typedef struct		s_list
{
	int				total;
	int				times_to_eat;
	uint64_t		start;
	uint64_t		dying;
	uint64_t		eating;
	uint64_t		sleeping;
	t_listtwo		*philosophers;
	pthread_mutex_t	*main_forks;
	pthread_mutex_t	main_print;
	pthread_mutex_t	philosopher_dead;
}					t_list;


int			main(int argc, char const **argv);

int			print_error(char const *str);
int			clean_semaphore(t_list *state);

int			start(t_list *p, int argc, char const **argv);

void		philosophers_eating(t_listtwo *philo);
void		remove_forks(t_listtwo *philo);
void		run_forks(t_listtwo *philo);

void		show_text(t_listtwo *philo, int p);

int			ft_strlen(char const *str);
int			ft_atoi(char const *str);
uint64_t	take_the_time(void);
void		ft_putnbr_fd(uint64_t n, int fd);

#endif
