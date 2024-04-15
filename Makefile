CFLAGS = -Wall -Wextra -Werror -Wformat=2 -ggdb -pedantic -Wunreachable-code -Wfloat-equal -Wstrict-overflow=5 -Warray-bounds -std=c99
OBJ = build/parse.o build/integer.o build/string.o
CC = gcc
NAME = libconfx.a

all : build $(NAME)

build:
	if [ ! -d "build/" ]; then \
		mkdir build; \
	fi

# compiling all to object files
build/%.o : src/%.c
	$(CC) $< $(CFLAGS) -c -o $@

$(NAME) : $(OBJ)
	ar rcs $(NAME) $(OBJ) 
clean : 
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all

test : all
	$(CC) $(CFLAGS) $(NAME) tests/main.c -o test
