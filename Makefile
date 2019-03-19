CC = gcc
CFLAGS = -lncurses -lm -Wall -ansi -pedantic -Wextra -Werror -g
DEPS = header.h
OBJ = main.o
OUT_EXE = sine

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT_EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o $(OUT_EXE)

install:
	cp ./$(OUT_EXE) /bin

rebuild: clean
	 make
