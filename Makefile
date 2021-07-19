SRCS	=	so_long_main.c so_long_body.c key.c map_create_utils.c  key_utils.c
FLAGS	=	-Wall -Werror -Wextra
CC		=	gcc
RM		=	rm -f
OBJS	=	$(SRCS:c=o)
INC		=	-I /usr/local/include -I libft/libft.h -I so_long.h
MLX		=	-L /usr/local/lib -lmlx -framework OpenGL -framework Appkit
LIB		=	-L. -lsolong
NAME	=	libsolong.a

all:	$(NAME)

%o: %c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): libft.a $(OBJS)
	ar rcs $(NAME) $(OBJS) ./libft/*o

run: compile
	./so_long map.ber

compile:
	$(CC) $(FLAGS) $(SRCS) $(INC) $(MLX) $(LIB) -o so_long

clean:
	$(RM) $(OBJS) ./a.out so_long 

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

libft.a:
	make -C ./libft
	
