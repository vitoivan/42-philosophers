CC = clang
CFLAGS = -Wall -Wextra -Werror -g -c 
LFLAGS = -pthread
NAME = philosophers

OBJ_DIR = dist
DIRS = 	$(OBJ_DIR) \
		$(OBJ_DIR)/utils

TARGETS = 	main.c \
			utils/usage_message.c
	
OBJECTS = $(addprefix $(OBJ_DIR)/, $(TARGETS:.c=.o))

all: $(NAME)

run: all
	./$(NAME) 5 800 200 200

$(NAME): $(DIRS)  $(OBJECTS) 
	$(CC)  $(OBJECTS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $< -o $@

$(DIRS):
	mkdir -p $(DIRS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re run