CC = clang
CFLAGS = -Wall -Wextra -Werror -g -c 
LFLAGS = -pthread
LIBFT = libs/libft/libft.a
NAME = philosophers

OBJ_DIR = dist
DIRS = 	$(OBJ_DIR) \
		$(OBJ_DIR)/utils

TARGETS = 	main.c \
			utils/usage_message.c
	
OBJECTS = $(addprefix $(OBJ_DIR)/, $(TARGETS:.c=.o))

all: $(NAME)

$(NAME): $(DIRS) $(LIBFT) $(OBJECTS) 
	$(CC)  $(OBJECTS) $(LFLAGS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

$(LIBFT):
	make -C libs/libft

clean:
	rm -rf $(OBJ_DIR)
	make clean -C libs/libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libs/libft

re: fclean all


.PHONY: all clean fclean re