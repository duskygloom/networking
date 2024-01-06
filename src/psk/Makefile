CC 		= gcc
DIR 	= build
ARGS	= -Wall -lm -g
BINARY 	= a.exe
OBJECTS = $(DIR)/main.o $(DIR)/encoder.o $(DIR)/noise_addition.o

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $(BINARY) -g

$(DIR)/%.o: %.c
	$(CC) $^ -o $@ -c -g

clean:
	rm $(DIR)/*
	