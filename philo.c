/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:36:51 by ybouchra          #+#    #+#             */
/*   Updated: 2023/08/19 08:27:48 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


int valid_args(char *s)
{
	int i;
	
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while(s[i] == '0')
		i++;
	if(ft_strlen(s + i) > 10)
		return(0);
		
	 if(ft_atoi(s) > INT_MAX  || ft_atoi(s) < 0)
	 	return(0);

	return(1);
}

void add_value(char **av)
{
	int i ;
	t_vars vars;
	
	i = 0;
		vars.number_of_philosophers = ft_atoi(av[1]);
		vars.number_of_forks = ft_atoi(av[1]);
		vars.time_to_die = ft_atoi(av[2]);
		vars.time_to_eat = ft_atoi(av[3]);
		vars.time_to_sleep = ft_atoi(av[4]);
		if(av[5])
		vars.number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);

		vars.id = malloc(sizeof(int) * vars.number_of_philosophers);
			while (vars.number_of_philosophers > i++)
			{
				vars.id[i] = i; 
				printf("xxx :-> %d\n",vars.id[i]);
			}
		
}

// void print_info(char **av)
// {
// 	t_vars vars;
// 		printf("nbr_philo : %d\n",vars.number_of_philosophers);
// 		printf("time_die : %d\n",vars.time_to_die);
// 		printf("time_eat : %d\n",vars.time_to_eat);
// 		printf("time_sleep : %d\n",vars.time_to_sleep);
// 		if(av[5])
// 		printf("nbr_time_meal : %d\n",vars.number_of_times_each_philosopher_must_eat);
// }






void *thread_func(void *arg){

	t_vars *vars = (t_vars*)arg;
	pthread_mutex_lock(&vars->mutex);
		for(int x = 0; x < 1000000; x++ )
			vars->num++;
	pthread_mutex_unlock(&vars->mutex);
	printf("xxx :-> %d\n",vars->num);
	return(NULL);
}

void create_threads()
{
	t_vars vars;
	int i = -1;
	int nbr_threads = vars.number_of_philosophers;
	
    pthread_t threads[nbr_threads];
	vars.num = 0;
	
	pthread_mutex_init(&vars.mutex, NULL);
    while (nbr_threads > ++i)
	{
        if (pthread_create(&threads[i], NULL, thread_func, &vars) != 0) {
            write(2, "error_pthread_create", 20);return;}
		if (pthread_join(threads[i], NULL) != 0) {
            write(2, "failed_pthread_to_join ", 18);return;}
    }	
			pthread_mutex_destroy(&vars.mutex);

}


int main(int ac, char **av)
{
	if(ac >= 5 && ac <= 6)
	{
		int i;
		
		i = 0;
		while(av[++i])
		{
			if(!is_digits(av[i]) || !valid_args(av[i]) )
				return(write(2,"ERROR\n", 6), 0);
		}
		add_value(av);
		create_threads();

	}
	else
		return(write(2,"ERROR\n", 6), 1);
	
}