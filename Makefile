CC = clang
CFLAGS = -Wall -Wextra -Werror -g -c 
LFLAGS = -pthread
NAME = philo/philo

OBJ_DIR = dist
DIRS = 	$(OBJ_DIR)

TARGETS = 	main.c \
			validate_args.c \
			ft_isdigit.c \
			context.c \
			ft_strlen.c \
			ft_strcmp.c \
			ft_atoi.c
	
OBJECTS = $(addprefix $(OBJ_DIR)/, $(TARGETS:.c=.o))

all: $(NAME)

run: all
	./$(NAME) 1 50 200 200

$(NAME): $(DIRS) $(OBJECTS) 
	$(CC)  $(OBJECTS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: philo/%.c
	$(CC) $(CFLAGS) $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)

	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) 2 800 200 200


.PHONY: all clean fclean re run test