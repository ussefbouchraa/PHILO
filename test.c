/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouchra <ybouchra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 02:33:31 by ybouchra          #+#    #+#             */
/*   Updated: 2023/08/16 11:15:18 by ybouchra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>


// int main()
// {
// 	int pid = fork();
	
// 	if(pid == -1)
// 		return(0);

// 	if(pid > 0)
// 	{
// 	wait(NULL);
// 	printf("X : i'm the pid of parent_process : %d\n",getpid());
// 	printf("X : i'm the pid of child_process : %d\n\n",pid);
// 	}
	
// 	if(pid == 0)
// 	{
// 	printf("x : i'm the pid of parent_process : %d\n",getppid());
// 	printf("x : i'm the pid of child_process : %d\n",getpid());
// 	}
// 	// while(1)
// 	// {
// 	// }
		
// 		return(0);
// }


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <pthread.h>

// int x = 2;

// void *ult(){
//     printf("skorp : %d\n",++x);
//     return(0);
// }
// void *ult1(){
//     printf("arisan : %d\n",x);
//     return(0);
// }

// int main()
// {
//     pthread_t T1, T2;
    
//     pthread_create(&T1, NULL, &ult, NULL);
//     pthread_create(&T2, NULL, &ult1, NULL);
    
//     pthread_join(T1, NULL);
//     pthread_join(T2, NULL);
    
//     // pthread_exit(NULL);
    
// return(0);
// }


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main()
{
	int pid = fork();
	int x = 10;
	if(pid == -1)
		return(0);

	
	if(pid == 0)
	printf("x: %d\n",x);
	    printf("X: %d\n",++x);
		
		return(0);
}