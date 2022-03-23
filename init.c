/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:35:41 by slott             #+#    #+#             */
/*   Updated: 2022/03/23 17:16:57 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

void	init_s(t_phil *s, int argc, char *argv[])
{
	s->n_philo = ft_atoi(argv[1]);
	s->t_die = ft_atoi(argv[2]);
	s->t_eat = ft_atoi(argv[3]);
	s->t_sleep = ft_atoi(argv[4]);
	s->ok = 0;
	if (argc == 6)
		s->max_meals = ft_atoi(argv[5]);
}

int	init_phil(t_phil *s)
{
	int	i;

	i = 0;
	while (i < s->n_philo)
	{
		s->l_meal[i].tv_sec = 0;
		i++;
	}
	i = 0;
	while (i < s->n_philo)
	{
		s->n_meal[i] = 0;
		i++;
	}
	i = 0;
	while (i < s->n_philo)
	{
		if (pthread_create(&s->thread[i], NULL, &routine, s))
			return (1);
		i++;
		usleep(10);
	}
	return (0);
}

int	init_mutex(t_phil *s)
{
	int	i;

	i = 0;
	while (i < s->n_philo)
	{
		if (pthread_mutex_init(&s->mutex[i], NULL))
			return (1);
		i++;
	}
	return (0);
}

int	start_p(t_phil *s)
{
	int	i;

	i = 0;
	while (s->l_meal[i].tv_sec != 0)
		i++;
	gettimeofday(&s->l_meal[i], NULL);
	return (i);
}

int	init_malloc(t_phil *s)
{
	s->thread = malloc(s->n_philo * sizeof(pthread_t));
	s->l_meal = malloc(s->n_philo * sizeof(struct timeval));
	s->mutex = malloc(s->n_philo * sizeof(pthread_mutex_t));
	s->n_meal = malloc(s->n_philo * sizeof(int));
	if (!s->thread || !s->l_meal || !s->mutex || !s->n_meal)
		return (1);
	return (0);
}
