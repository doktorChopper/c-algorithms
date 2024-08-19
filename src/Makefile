CC = gcc
RM = rm -rf
EXE = main
SRC = main.c \
	  stack.c \

OBJ = $(SRC:.c=.o)
LIB = libstack.so

all: $(EXE)

$(EXE): main.o $(LIB)
	$(CC) -o $@ -L. -lstack

$(LIB): $(OBJ)
	$(CC) -shared -o $@ $^

main.o: main.c
	$(CC) -c main.c

stack.o: stack.c
	$(CC) -c -fPIC stack.c

clean:
	$(RM) *.o $(EXE) *.so

