/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:36:51 by ybouchra          #+#    #+#             */
/*   Updated: 2023/08/30 05:04:03 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		ft_usleep(100);
	while (ph->meals < ph->vars->number_of_meals) 
	{
		pthread_mutex_lock(&ph->fork);
		print("has taken a fork", ph);
		pthread_mutex_lock(ph->next_fork);
		print("has taken a fork", ph);
		pthread_mutex_lock(&ph->lock_lm);
		ph->last_meal = time_now();
		pthread_mutex_unlock(&ph->lock_lm);
		print("is eating", ph);
		ft_usleep(ph->vars->time_to_eat);
		pthread_mutex_lock(&ph->vars->lock_m);
		ph->meals += (ph->vars->number_of_meals != -1);
		pthread_mutex_unlock(&ph->vars->lock_m);
		pthread_mutex_unlock(ph->next_fork);
		pthread_mutex_unlock(&ph->fork);
		print("is sleeping", ph);
		(ft_usleep(ph->vars->time_to_sleep), print("is thinking", ph));
	}
	return (NULL);
}

void	check_died(t_philo *philosopher, t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->num_of_philo > i)
	{
		pthread_mutex_lock(&vars->lock_m);
		if (philosopher[i].meals == vars->number_of_meals)
			break ;
		pthread_mutex_unlock(&vars->lock_m);
		pthread_mutex_lock(&philosopher[i].lock_lm);
		if (time_now() - philosopher[i].last_meal > vars->time_to_die)
		{
			pthread_mutex_lock(&vars->print);
			usleep(1000);
			printf("%zu\t%d\t%s\n", time_now() - philosopher[i].start_time,
				philosopher[i].id, "died");
			break ;
		}
		pthread_mutex_unlock(&philosopher[i].lock_lm);
		i++;
		if (i == vars->num_of_philo)
			i = 0;
	}
}

int	create_threads(t_philo *philosopher, t_vars *vars)
{
	int	i;

	i = -1;
	while (vars->num_of_philo > ++i)
	{
		if (pthread_create(&philosopher[i].tid, NULL, routine, &philosopher[i]))
			return (printf("failed_creation_pthread"), 0);
		if (pthread_detach(philosopher[i].tid))
			return (printf("failed_join_pthread"), 0);
	}
	check_died(philosopher, vars);
	return (1);
}

t_philo	*init_philo( t_vars *vars)
{
	t_philo	*philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo) * vars->num_of_philo);
	if (!philo)
		return (NULL);
	while (vars->num_of_philo > ++i)
	{
		philo[i].id = i + 1;
		philo[i].vars = vars;
		philo[i].start_time = time_now();
		philo[i].last_meal = philo[i].start_time;
		philo[i].meals = (philo->vars->number_of_meals == -1) * (-2);
		pthread_mutex_init(&philo[i].fork, NULL);
		pthread_mutex_init(&philo[i].lock_lm, NULL);
		if (i + 1 == vars->num_of_philo)
			philo[i].next_fork = &philo[0].fork;
		else
			philo[i].next_fork = &philo[i + 1].fork;
	}
	return (philo);
}

int	main(int ac, char **av)
{
	t_vars	vars;
	t_philo	*philosophers;
	int		i;

	i = 0;
	philosophers = NULL;
	if (ac >= 5 && ac <= 6)
	{
		while (av[++i])
		{
			if (!is_digits(av[i]) || !valid_args(av[i]))
				return (write(2, "ERROR\n", 6), 0);
		}
		init_vars(&vars, av);
		philosophers = init_philo(&vars);
		create_threads(philosophers, &vars);
		destroy_philos(philosophers, &vars);
		free(philosophers);
	}
	else
		return (write(2, "ERROR\n", 6), 1);
}
