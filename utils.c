/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:54:18 by slott             #+#    #+#             */
/*   Updated: 2022/03/23 15:16:57 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	c;
	int	m;
	int	r;

	m = 0;
	c = 0;
	r = 0;
	if (!str)
		return (-1);
	while (str[c] > 47 && str[c] < 58 && str[c])
	{
		r = r * 10 + (str[c] - '0');
		c++;
	}
	if (str[c])
		return (-1);
	return (r);
}

long	get_time(t_phil *s)
{
	struct timeval	time;
	long			time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec - s->t_start.tv_sec) * 1000;
	time_ms += (time.tv_usec - s->t_start.tv_usec) / 1000;
	return (time_ms);
}

int	conv_id(t_phil *s, int id)
{
	if (id == -1)
		return (s->n_philo - 1);
	else if (id == -2)
		return (s->n_philo - 2);
	else
		return (id);
}

void	join_all(t_phil *s)
{
	int	i;

	i = 0;
	while (i < s->n_philo)
	{
		pthread_join(s->thread[i], NULL);
		i++;
	}
}
