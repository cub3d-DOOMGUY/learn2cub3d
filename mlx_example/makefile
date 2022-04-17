
NAME := program.out
LIB := -lmlx -lXext -lX11 -lm -lz
CC := clang

$(NAME): $(SRC)
	$(CC)  -Lmlx_linux  $^ $(LIB) -o $@

all: $(NAME)

run:
	./$(NAME)

clean:
	rm -f $(NAME) *.o

re: clean all


1: clean
	make SRC=01_untextured_raycast.c

2: clean
	make SRC=02_textured_raycast.c

3: clean
	make SRC=03_img_textured_raycast.c

4: clean
	make SRC=04_floor_ceiling.c

5: clean
	make SRC=05_sprite_raycast.c

