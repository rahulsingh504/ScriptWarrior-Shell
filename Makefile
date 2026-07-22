# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -I./src
# ...existing code...
SRC = src/main.c src/commands.c src/scheduler.c src/utils.c src/history.c src/auth.c src/alias.c
# ...existing code...
OBJ = $(SRC:.c=.o)
TARGET = scriptwarrior_shell

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean