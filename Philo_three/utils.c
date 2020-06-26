/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancarlosmartineznavas <juancarlosmart    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 18:51:38 by juancarlosm       #+#    #+#             */
/*   Updated: 2020/03/21 19:38:14 by juancarlosm      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philothree.h"

int						ft_strlen(char const *str)
{
	int					i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int						ft_atoi(char const *str)
{
	int					i;
	int					start;
	int					neg;
	int					res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' ||
			str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	neg = (str[i] == '-') ? -1 : 1;
	if (neg == -1 || str[i] == '+')
		i++;
	start = i;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res * neg);
}

void					ft_putnbr_fd(uint64_t n, int fd)
{
	char				str[13];
	int					len;

	if (n == 0)
		str[0] = '0';
	len = 0;
	while (n != 0)
	{
		str[len++] = '0' + (n % 10);
		n = (n / 10);
	}
	if (len > 0)
		len--;
	while (len >= 0)
		write(fd, &str[len--], 1);
}

uint64_t					take_the_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

int							ft_strcpy(char *dst, const char *src)
{
	int						i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (i);
}
