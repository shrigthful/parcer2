NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
FILES = minishell.c \
	get_next_line.c \
	string1.c \
	string2.c \
	string3.c \
	string4.c \
	string5.c \
	linked_list.c \
	parsing.c \
	qoutes.c \
	replace_env.c \

OFILES = $(FILES:.c=.o)
OBFILES = $(BFILES:.c=.o)

all : $(NAME) clean

$(NAME) : $(OFILES)
	$(CC) -fsanitize=address $(CFLAGS) $(OFILES) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $^

clean :
	rm -f $(OFILES) $(OBFILES)

fclean : clean
	rm -f $(NAME)

re : fclean all
