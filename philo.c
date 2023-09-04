/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:36:51 by ybouchra          #+#    #+#             */
/*   Updated: 2023/09/03 03:51:46 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		ft_usleep(100);
	while (1)
	{
		if (pthread_mutex_lock(&ph->fork))
			return (NULL);
		print("has taken a fork", ph);
		if (pthread_mutex_lock(ph->next_fork))
			return (NULL);
		print("has taken a fork", ph);
		is_eating(ph);
		if (pthread_mutex_unlock(ph->next_fork))
			return (NULL);
		if (pthread_mutex_unlock(&ph->fork))
			return (NULL);
		print("is sleeping", ph);
		ft_usleep(ph->vars->time_to_sleep);
		print("is thinking", ph);
	}
	return (NULL);
}

void	check_died(t_philo *philosopher, t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->num_of_philo > i)
	{
		if (pthread_mutex_lock(&vars->lock_m))
			return ;
		if (philosopher[i].vars->finish_eats == vars->num_of_philo)
			break ;
		pthread_mutex_unlock(&vars->lock_m);
		if (pthread_mutex_lock(&philosopher[i].lock_lm))
			return ;
		if (time_now() - philosopher[i].last_meal > vars->time_to_die)
		{
			if (pthread_mutex_lock(&vars->print))
				return ;
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
		philo[i].meals = 0;
		if (pthread_mutex_init(&philo[i].fork, NULL))
			return (NULL);
		if (pthread_mutex_init(&philo[i].lock_lm, NULL))
			return (NULL);
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
