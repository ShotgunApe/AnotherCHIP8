CC = gcc
CFLAGS = `pkg-config --cflags sdl3`
LDFLAGS = `pkg-config --libs sdl3`

SRCS := src/main.c src/components/window.c
OBJS = $(SRCS:src/%.c=build/%.o)
TARGET = build/AnotherCHIP8

TEST_SRCS := tests/test_main.c
TEST_OBJS = $(TEST_SRCS:tests/%.c=build/tests/%.o)
TEST_TARGET = build/tests/test

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Main object files
build/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Test object files
build/tests/%.o: tests/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_TARGET): $(TEST_OBJS) $(filter-out build/main.o, $(OBJS))  # exclude main.o
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: test
test: $(TEST_TARGET)
	clear
	./$(TEST_TARGET)

.PHONY: clean
clean:
	rm -rf build