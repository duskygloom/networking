CC = gcc
DIR = build
APP = a.exe
OBJECTS = $(DIR)/encoder.o $(DIR)/ask_noise_addition.o $(DIR)/main.o

all: $(APP)

$(APP): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(APP) -g

$(DIR)/%.o: %.c
	$(CC) $^ -o $@ -c

clean:
	rm $(DIR)/*
