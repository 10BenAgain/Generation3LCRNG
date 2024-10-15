BINARY	:= bin
CC		:= gcc

SOURCE	:= src
BUILD	:= build

OUTPUT	:= $(BUILD)/$(BINARY)
CFLAGS	:= -Wall -Wextra -g

CFILES	:= $(wildcard *.c) $(wildcard $(SOURCE)/*.c)
OBJECTS	:= $(patsubst %.c,$(BUILD)/%.o,$(notdir $(CFILES)))

# Creates an executable for the IV calculator in the build directory, can be executed with `./build/ivs 5 0 45 20 0 0`
ivs: iv_calc.o $(SOURCE)/pokemon.o
	$(CC) $(CFLAGS) $(SOURCE)/pokemon.o iv_calc.o -o $(BUILD)/ivs

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CC) -o $@ $^

$(BUILD)/%.o:$(SOURCE)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD)/%.o:%.c
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ $<

clean: all
	rm $(BUILD)/*.o
