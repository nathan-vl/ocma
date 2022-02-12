CC = gcc
CFLAGS = -Iinclude -O3 #-g -Wall -Wextra -Wfloat-equal -Wpedantic -fsanitize=address

BUILD = build

SOURCES = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,$(BUILD)/%.o,$(SOURCES))

OUT_OBJ = bot-pesca

%.o:
	$(CC) $(CFLAGS) -c -o $@ $(patsubst $(BUILD)/%.o,src/%.c,$@)

$(OUT_OBJ): makeBuildDir $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

makeBuildDir:
	mkdir -p $(BUILD)

.PHONY: clean

clean:
	rm -r $(BUILD)
