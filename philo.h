/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slott <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:48:04 by slott             #+#    #+#             */
/*   Updated: 2022/03/23 17:17:01 by slott            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				ok;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				max_meals;
	int				*n_meal;
	pthread_t		*thread;
	struct timeval	*l_meal;
	struct timeval	t_start;
	pthread_mutex_t	*mutex;
}	t_phil;

int		ft_error(char *str);
int		ft_atoi(const char *str);
int		init_phil(t_phil *s);
void	*routine(void *ss);
int		start_p(t_phil *s);
int		init_mutex(t_phil *s);
long	get_time(t_phil *s);
int		conv_id(t_phil *s, int id);
int		check_end(t_phil *s, int argc);
int		routine_suite(t_phil *s, int id);
void	join_all(t_phil *s);
void	unlock_mutex(t_phil *s, int id);
void	init_s(t_phil *s, int argc, char *argv[]);
int		check_meals(t_phil *s, int argc);
void	ft_eat(t_phil *s);
void	ft_sleep(t_phil *s);
int		init_malloc(t_phil *s);

#endif
