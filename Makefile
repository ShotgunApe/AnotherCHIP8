CC = gcc
CFLAGS = `pkg-config --cflags sdl3`
LDFLAGS = `pkg-config --libs sdl3`

SRCS := src/main.c src/components/window.c
OBJS = $(SRCS:src/%.c=build/%.o)

TARGET = build/AnotherCHIP8

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf build