NAME = philo

CC = cc -Wall -Wextra -Werror -pthread
RM = rm -rf

FILES = philo.c utils.c 

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
