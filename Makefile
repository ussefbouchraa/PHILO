NAME = philo

CC = cc -Wall -Wextra -Werror 

FILES = philo.c utils_pars.c utils_philo.c

OBJS = $(FILES:.c=.o)


all	: $(NAME)

$(NAME) : $(OBJS)
	$(CC)  $^ -o $@

%.o : %.c philo.h
	$(CC) -c $< -o $@ 

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
