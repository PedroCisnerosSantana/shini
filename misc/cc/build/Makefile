SRC      = $(wildcard ../src/*.c)
CC       = gcc
CFLAGS   = -ggdb -Wall -Werror -I../src/include

all: cc clean

cc: $(SRC:.c=.o)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm ../src/*.o

