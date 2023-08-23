/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:37:03 by ybouchra          #+#    #+#             */
/*   Updated: 2023/08/21 01:17:48 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t ft_strlen(char *s)
{
	if(!s)
		return(0);
	size_t i;
	
	i = 0;
	while(s[i])
		i++;

return(i);
}

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

int is_digits(char *s)
{
	if(!s || !*s)
		return(0);
	if(s[0] == '+')
		s++;
	if (!*s) return (0);
	while(*s)
	{
		if(!(*s >= '0' && *s <= '9'))
			return(0);
		s++;
	}
	return(1);
}
long ft_atoi(char *s)
{
	int sign;
	long res;

	sign = 1;
	res = 0;
	if(!s)
		return(0);
	while(*s >= 9 && *s <= 13)
		s++;
	if(*s == '-' || *s == '+')
		{
			if(*s == '-')
				sign *= -1;
			s++;
		}
	while(*s >= '0' && *s <= '9')
		{
			res = res * 10 + (*s - 48);
			s++;
		}
	return(res * sign);
	
}