/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 04:56:09 by ybouchra          #+#    #+#             */
/*   Updated: 2023/09/03 00:54:02 by ybouchra         ###   ########.fr       */
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

void	print(char *msg, t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->vars->print);
	printf("%zu\t%d %s\n", time_now() - philosopher->start_time,
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
	if (pthread_mutex_init(&vars->print, NULL))
		return ;
	if (pthread_mutex_init(&vars->lock_m, NULL))
		return ;
}

void	is_eating(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->lock_lm))
		return ;
	ph->last_meal = time_now();
	if (pthread_mutex_unlock(&ph->lock_lm))
		return ;
	print("is eating", ph);
	ft_usleep(ph->vars->time_to_eat);
	if (pthread_mutex_lock(&ph->vars->lock_m))
		return ;
	ph->meals += (ph->vars->number_of_meals != -1);
	ph->vars->finish_eats += ph->meals == ph->vars->number_of_meals;
	if (pthread_mutex_unlock(&ph->vars->lock_m))
		return ;
}
