/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 00:01:12 by ybouchra          #+#    #+#             */
/*   Updated: 2023/09/03 00:28:33 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX  2147483647

typedef struct s_vars
{
	int				num_of_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				number_of_meals;
	int				finish_eats;
	pthread_mutex_t	lock_m;
	pthread_mutex_t	print;

}	t_vars;
typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	pthread_mutex_t	lock_lm;
	size_t			start_time;
	size_t			last_meal;
	int				meals;
	t_vars			*vars;
}	t_philo;

size_t	ft_strlen(char *s);
int		valid_args(char *s);
int		is_digits(char *s);
long	ft_atoi(char *s);
size_t	time_now(void);

void	is_eating(t_philo *ph);
void	ft_usleep(size_t t_ms);
void	init_vars(t_vars *vars, char **av);
void	print(char *msg, t_philo *philosopher);
void	destroy_philos( t_philo *philosopher, t_vars *vars);

#endif