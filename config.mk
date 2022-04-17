NAME := program.out
LIB_PATH := ../lib
CFLAGS := -Wall -Werror -Wextra
LIBFT := $(LIB_PATH)/libscarf/libft.a

INC := -I$(LIB_PATH) -I include/ -I include/types \
       -I ../lib/libscarf/include/ -I ../lib/libscarf/include/types/
LIB := -L$(LIB_PATH)/mlx_linux -L$(LIB_PATH)/libscarf \
       -lmlx -lft -lXext -lX11 -lm

CC := clang

PKGS = engine raycast data

SRC = $(wildcard src/**/*.c) src/main.c
OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(INC) $(CFLAGS) $^ $(LIB) -o $@

$(LIBFT): 
	make -C $(LIB_PATH)/libscarf/

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
