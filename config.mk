NAME := program.out
LIB_PATH := ../lib
INC := -I$(LIB_PATH)
LIB := -L$(LIB_PATH)/mlx_linux -lmlx -lXext -lX11 -lm
CC := clang

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(INC)  -c $< -o $@

$(NAME): $(OBJ)
	make docs
	$(CC) $(INC) $^ $(LIB) -o $@

all: $(NAME)

run:
	./$(NAME)

clean:
	rm -f $(NAME) *.o

re: clean all

docs:
	hgen -I engine.h $(SRC)
