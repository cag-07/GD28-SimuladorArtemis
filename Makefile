# Makefile

CC = gcc

CFLAGS = -Wall -Wextra

LDFLAGS = -lm

TARGET = simulador

SRCS = main.c simulador.c validaciones.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c simulador.h validaciones.h
	$(CC) $(CFLAGS) -c $<

clean:
	del /Q *.o $(TARGET).exe 2>nul || rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
