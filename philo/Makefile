CC = clang
CFLAGS = -Wall -Wextra -Werror -c -g
DEBUG = -gdwarf-4
LFLAGS = -pthread
DEBUG = -gdwarf-4 -fsanitize=thread
LFLAGS = -pthread -fsanitize=thread
NAME = philo

OBJ_DIR = dist
DIRS = 	$(OBJ_DIR)
VALGRIND = valgrind --show-leak-kinds=all --leak-check=full --track-origins=yes

TARGETS = 	main.c \
			validate_args.c \
			ft_isdigit.c \
			context.c \
			forks.c \
			forks_utils.c \
			ft_strlen.c \
			ft_strcmp.c \
			ft_sleep.c \
			print_action.c \
			monitor.c \
			eat.c \
			think.c \
			ft_atoi.c
	
OBJECTS = $(addprefix $(OBJ_DIR)/, $(TARGETS:.c=.o))

all: $(NAME)

run: all
	./$(NAME) 5 460 200 200

$(NAME): $(DIRS) $(OBJECTS) 
	$(CC)  $(OBJECTS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG) $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	$(VALGRIND) ./$(NAME) 4 600 200 200 5


.PHONY: all clean fclean re run test
