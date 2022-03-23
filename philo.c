/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:47:24 by slott             #+#    #+#             */
/*   Updated: 2022/03/23 17:16:53 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	main(int argc, char *argv[])
{
	t_phil	s;
	int		id_dead;

	if (argc != 5 && argc != 6)
		return (ft_error("Error: argument\n"));
	init_s(&s, argc, argv);
	if (s.n_philo == -1 || s.t_die == -1 || s.t_eat == -1
		|| s.t_sleep == -1 || s.max_meals == -1)
		return (ft_error("Error: argument\n"));
	if (init_malloc(&s))
		return (1);
	gettimeofday(&s.t_start, NULL);
	if (init_mutex(&s))
		return (1);
	if (init_phil(&s))
		return (1);
	id_dead = check_end(&s, argc);
	if (id_dead && s.n_philo != 0)
	{
		s.ok = 1;
		join_all(&s);
		if (id_dead != -1)
			printf("%ld %d died\n", get_time(&s), id_dead - 1);
	}
	return (0);
}

void	*routine(void *ss)
{
	int		id;
	t_phil	*s;

	s = (t_phil *)ss;
	pthread_mutex_lock(&s->mutex[0]);
	id = start_p(s);
	pthread_mutex_unlock(&s->mutex[0]);
	if (id % 2 == 0)
		ft_eat(s);
	while (id % 2 == 1 && s->l_meal[s->n_philo - 1].tv_sec == 0)
		usleep(1);
	while (s->n_philo == 1)
	{
		if (s->ok == 1)
			return (NULL);
	}
	while (1)
	{
		if (s->ok == 1)
			return (NULL);
		if (routine_suite(s, id))
			return (NULL);
	}
}

int	routine_suite(t_phil *s, int id)
{
	if (s->ok == 1)
		return (1);
	pthread_mutex_lock(&s->mutex[id]);
	pthread_mutex_lock(&s->mutex[conv_id(s, id - 1)]);
	printf("%ld %d has taken a fork\n", get_time(s), id);
	printf("%ld %d has taken a fork\n", get_time(s), id);
	gettimeofday(&s->l_meal[id], NULL);
	if (s->ok == 1)
	{
		unlock_mutex(s, id);
		return (1);
	}
	printf("%ld %d is eating\n", get_time(s), id);
	s->n_meal[id]++;
	ft_eat(s);
	pthread_mutex_unlock(&s->mutex[conv_id(s, id - 1)]);
	pthread_mutex_unlock(&s->mutex[id]);
	if (s->ok == 1)
		return (1);
	printf("%ld %d is sleeping\n", get_time(s), id);
	ft_sleep(s);
	if (s->ok == 1)
		return (1);
	printf("%ld %d is thinking\n", get_time(s), id);
	return (0);
}

int	check_end(t_phil *s, int argc)
{
	struct timeval	time;
	int				i;
	long			diff;
	int				c;

	while (1)
	{
		i = 0;
		c = 0;
		gettimeofday(&time, NULL);
		while (i < s->n_philo && s->l_meal[s->n_philo - 1].tv_sec != 0)
		{
			diff = (time.tv_sec - s->l_meal[i].tv_sec) * 1000;
			diff += (time.tv_usec - s->l_meal[i].tv_usec) / 1000;
			if (diff >= s->t_die)
				return (i + 1);
			i++;
		}
		if (check_meals(s, argc))
			return (-1);
		usleep(100);
	}
	return (0);
}
