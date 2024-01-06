CC		= gcc
ARGS	= -Wall -g
BUILD	= build
BINARY	= a.exe
OBJECTS	= $(BUILD)/stream.o

all: main

main: $(BUILD)/main.o $(OBJECTS)
	$(CC) $^ -o $(BINARY) $(ARGS)

$(BUILD)/%.o: %.c
	$(CC) $^ -o $@ -c $(ARGS)

init:
	mkdir $(BUILD)

clean:
	rm $(BUILD)/*.o

run:
	./$(BINARY) ./bitstream.dat
