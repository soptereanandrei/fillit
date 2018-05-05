NAME = fillit

all: $(NAME)

$(NAME):
	gcc -Wall -Wextra -Werror -c main.c converter.c generate.c check_file.c solver_fn1.c ft_memset.c ft_putchar.c ft_putstr.c ft_strsplit.c ft_bzero.c -I.fillit.h
	gcc -Wall -Wextra -Werror main.o converter.o generate.o check_file.o solver_fn1.o ft_memset.o ft_putchar.o ft_putstr.o ft_strsplit.o ft_bzero.o -I.fillit.h -o $(NAME)

clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)

re: fclean all
