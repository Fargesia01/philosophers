/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:58:55 by slott             #+#    #+#             */
/*   Updated: 2022/03/23 17:03:39 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	unlock_mutex(t_phil *s, int id)
{
	pthread_mutex_unlock(&s->mutex[conv_id(s, id)]);
	pthread_mutex_unlock(&s->mutex[id]);
}

int	check_meals(t_phil *s, int argc)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (i < s->n_philo && argc == 6)
	{
		if (s->n_meal[i] >= s->max_meals)
			c++;
		i++;
	}
	if (c == s->n_philo)
		return (1);
	return (0);
}

void	ft_eat(t_phil *s)
{
	long	start;
	long	time;

	start = get_time(s);
	time = start;
	while (time - start < s->t_eat && s->ok == 0)
	{
		time = get_time(s);
		usleep(100);
	}
}

void	ft_sleep(t_phil *s)
{
	long	start;
	long	time;

	start = get_time(s);
	time = start;
	while (time - start < s->t_sleep && s->ok == 0)
	{
		time = get_time(s);
		usleep(100);
	}
}
