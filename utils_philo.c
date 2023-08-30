/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:56:09 by ybouchra          #+#    #+#             */
/*   Updated: 2023/08/30 02:45:12 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t t_ms)
{
	size_t	start;

	start = time_now();
	while ((time_now() - start) < t_ms)
		usleep(100);
}

size_t	time_now(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	print(char *msg, t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->vars->print);
	printf("%zu\t%d\t%s\n", time_now() - philosopher->start_time,
		philosopher->id, msg);
	pthread_mutex_unlock(&philosopher->vars->print);
}

void	destroy_philos(t_philo *philosopher, t_vars *vars)
{
	int	i;

	i = -1;
	while (vars->num_of_philo > ++i)
		pthread_mutex_destroy(&philosopher[i].fork);
	pthread_mutex_destroy(&vars->print);
	pthread_mutex_destroy(&vars->lock_m);
	pthread_mutex_destroy(&philosopher[i].lock_lm);
}

void	init_vars(t_vars *vars, char **av)
{
	vars->num_of_philo = ft_atoi(av[1]);
	vars->time_to_die = ft_atoi(av[2]);
	vars->time_to_eat = ft_atoi(av[3]);
	vars->time_to_sleep = ft_atoi(av[4]);
	vars->finish_eats = 0;
	if (av[5])
		vars->number_of_meals = ft_atoi(av[5]);
	else
		vars->number_of_meals = -1;
	pthread_mutex_init(&vars->print, NULL);
	pthread_mutex_init(&vars->lock_m, NULL);
}
