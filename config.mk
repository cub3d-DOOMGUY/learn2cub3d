NAME := program.out
LIB_PATH := ../lib
CFLAGS := -Wall -Werror -Wextra
INC := -I$(LIB_PATH) -I include/ -I include/types
LIB := -L$(LIB_PATH)/mlx_linux -lmlx -lXext -lX11 -lm
CC := clang

PKGS = engine raycast data

SRC = $(wildcard src/**/*.c) src/main.c
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
	@set -e;\
		for p in $(PKGS); do\
			hgen -I include/$$p.h src/$$p ;\
		done

#1> /dev/null;\
