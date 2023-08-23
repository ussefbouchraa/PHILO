#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

#define INT_MAX  2147483647
#define INT_MIN  -2147483648


typedef struct s_vars
{	
	int			num_of_philo;
	long long	time_to_die;
	long long	time_to_eat;
	long long	time_to_sleep;
	int			number_of_meals;
} t_vars;

typedef struct s_philo
{
	int 			id;
	pthread_t		tid;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	t_vars			*vars;
} t_philo;

size_t ft_strlen(char *s);
long ft_atoi(char *s);
int is_digits(char *s);
int valid_args(char *s);

#endif