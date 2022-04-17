NAME := program.out
LIB_PATH := ../lib
CFLAGS := -Wall -Werror -Wextra
INC := -I$(LIB_PATH) -I include/
LIB := -L$(LIB_PATH)/mlx_linux -lmlx -lXext -lX11 -lm
CC := clang

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(INC) $(CFLAGS) $^ $(LIB) -o $@

all: $(NAME)

run:
	./$(NAME)

clean:
	rm -f $(NAME) *.o

re: clean all

docs:
	hgen -I engine.h $(SRC)
