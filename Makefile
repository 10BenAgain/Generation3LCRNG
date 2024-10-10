BINARY	:= bin
CC		:= gcc

SOURCE	:= src
BUILD	:= build

OUTPUT	:= $(BUILD)/$(BINARY)
CFLAGS	:= -Wall -Wextra -g

CFILES	:= $(wildcard *.c) $(wildcard $(SOURCE)/*.c)
OBJECTS	:= $(patsubst %.c,$(BUILD)/%.o,$(notdir $(CFILES)))

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



