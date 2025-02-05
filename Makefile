NAME= fdf
EXTRA= ./gnl/get_next_line_utils.o ./gnl/get_next_line.o
FILES= ./src/main.o ./src/draw.o ./src/map.o ./src/utils.o ./src/section.o ./src/distort.o $(EXTRA)
BONUS_FILES= ./src_bonus/main.o ./src_bonus/draw.o ./src_bonus/map.o ./src_bonus/utils.o ./src_bonus/section.o ./src_bonus/distort.o ./src_bonus/mouse_events.o ./src_bonus/pan_events.o ./src_bonus/events.o $(EXTRA)
CC=cc -Wall -Wextra -I ./$(MINILIBX) -ggdb
FLAG_EXEC=-Lmlx_linux -lmlx_Linux -L./$(MINILIBX) -Imlx_linux -lXext -lX11 -lm -lz
FLAG_OBJ=-Imlx_linux -O3

MINILIBX=minilibx-linux
GNL=gnl
LIBFT=libft

all: $(MINILIBX) $(LIBFT) $(GNL) $(NAME) 

$(MINILIBX):
	git clone git@github.com:42Paris/minilibx-linux.git $(MINILIBX)
	make -C ./$(MINILIBX)

$(GNL):
	git clone git@vogsphere.42.rio:vogsphere/intra-uuid-f0741049-8cdf-4570-ad4e-7e7dbfe7e7b9-6158753-vide-sou $(GNL)

$(LIBFT):
	git clone git@vogsphere.42.rio:vogsphere/intra-uuid-2800a959-95ad-4d3c-a22f-0993937cbfce-6122962-vide-sou $(LIBFT)
	make -C ./$(LIBFT)

$(NAME): $(FILES)
	$(CC) $^ ./libft/libft.a $(FLAG_EXEC) -o $(NAME)

.o: .c
	$(CC) $(FLAG_OBJ) -c $< -o $@

clean:
	rm -f $(FILES)

fclean: clean
	rm -f $(NAME)
	rm -rf $(MINILIBX)
	rm -rf $(LIBFT)
	rm -rf $(GNL)

re: clean all