NAME= fdf
FILES= ./main.o
CC=cc -Wall -Wextra -I ./$(MINILIBX_NAME) -ggdb
FLAG_EXEC=-Lmlx_linux -lmlx_Linux -L./$(MINILIBX_NAME) -Imlx_linux -lXext -lX11 -lm -lz
FLAG_OBJ=-Imlx_linux -O3
MINILIBX_NAME=minilibx-linux

all: $(MINILIBX_NAME) $(NAME) 

$(MINILIBX_NAME):
	git clone git@github.com:42Paris/minilibx-linux.git
	make -C ./$(MINILIBX_NAME)

$(NAME): $(FILES)
	$(CC) $^ $(FLAG_EXEC) -o $(NAME)

.o: .c
	$(CC) $(FLAG_OBJ) -c $< -o $@

clean:
	rm -f $(FILES)

fclean: clean
	rm -f $(NAME)
	rm -rf $(MINILIBX_NAME)

re: clean all