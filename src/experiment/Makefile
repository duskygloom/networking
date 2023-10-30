DIR = build
CC = gcc
OBJECTS = $(DIR)/main.o
BINARY = a.exe

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $(BINARY) -g

$(DIR)/%.o: %.c
	$(CC) $^ -o $@ -c

clean:
	rm $(DIR)/*
	