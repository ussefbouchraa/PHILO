/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:36:51 by ybouchra          #+#    #+#             */
/*   Updated: 2023/08/23 12:47:26 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg){

	t_philo *philosopher = (t_philo *)arg;
	if (philosopher->id % 2 == 0){
		usleep(100);
	}
	while (1){
		pthread_mutex_lock(&philosopher->fork);
		printf("philo[%d] has taken a fork1\n", philosopher->id);
		pthread_mutex_lock(philosopher->next_fork);
		printf("philo[%d] has taken a fork2\n", philosopher->id);
		printf("philo[%d] is eating\n", philosopher->id);
		usleep(philosopher->vars->time_to_eat * 1000);
		//todo : sleep time to eat
		// update lastmealtime 
		// update numberofmeals
		pthread_mutex_unlock(&philosopher->fork);
		pthread_mutex_unlock(philosopher->next_fork);
		printf("philo[%d] is sleeping\n", philosopher->id);
		usleep(philosopher->vars->time_to_sleep  * 1000);
		
		// todo : sleep time to sleep 
		printf("philo[%d] is thinking\n", philosopher->id);

	}

	return(NULL);
}


void	init_vars(t_vars *vars, char **av)
{
	vars->num_of_philo = ft_atoi(av[1]);	
	vars->time_to_die = ft_atoi(av[2]);	
	vars->time_to_die = ft_atoi(av[3]);	
	vars->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		vars->number_of_meals = ft_atoi(av[5]);
	else
		vars->number_of_meals = -1;
		
}
t_philo *init_philo( t_vars *vars)
{
	t_philo *philosopher;
	int i;

	i = -1;	
	philosopher = malloc(sizeof(t_philo) * vars->num_of_philo);
	if(!philosopher)
		return(NULL);

	while( vars->num_of_philo > ++i)
	{
		philosopher[i].id = i + 1;
		philosopher[i].vars = vars;
		pthread_mutex_init(&philosopher[i].fork, NULL);
		
		if(i + 1 == vars->num_of_philo)
			philosopher[i].next_fork = &philosopher[0].fork;
		else
			philosopher[i].next_fork = &philosopher[i + 1].fork;
	}
	return(philosopher);
	
}

int create_threads(t_philo *philosopher, t_vars *vars)
{
	int i = -1;
	while(vars->num_of_philo > ++i)
	{
		if(pthread_create(&philosopher[i].tid, NULL, routine, &philosopher[i]))
			return(printf("failed_creation_pthread"), 0);
	}
	i = -1;
	while(vars->num_of_philo > ++i)
	{
		if(pthread_join(philosopher[i].tid, NULL))
			return(printf("failed_join_pthread"), 0);
	}
			
	return(1);
}


int main(int ac, char **av)
{
	t_vars	vars;
	t_philo *philosophers;

	
	int i;
	
	i = 0;
	if(ac >= 5 && ac <= 6)
	{
		while(av[++i])
		{
			if(!is_digits(av[i]) || !valid_args(av[i]))
				return(write(2,"ERROR\n", 6), 0);
		}
		init_vars(&vars, av);
		philosophers = init_philo(&vars);
		create_threads(philosophers, &vars);
	}
	else
		return(write(2,"ERROR\n", 6), 1);
}
