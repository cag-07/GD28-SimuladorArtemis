# Makefile

CC = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic

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
	rm -f *.o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
