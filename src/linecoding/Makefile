CC = gcc
DIR = build
APP = a.out
OBJECTS = $(DIR)/encoder.o $(DIR)/main.o

all: $(APP)

$(APP): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(APP) -g

$(DIR)/%.o: %.c
	$(CC) $^ -o $@ -c

clean:
	rm $(DIR)/*.o
	rm $(APP)
