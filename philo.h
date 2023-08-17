#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#define INT_MAX  2147483647
#define INT_MIN  -2147483648

typedef struct s_vars
{
	int number_of_philosophers;
	int number_of_forks;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
}t_vars;

size_t ft_strlen(char *s);
long ft_atoi(char *s);
int is_digits(char *s);

#endif