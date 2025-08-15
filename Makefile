CC=gcc-15
CFLAGS=-Wall -Werror -Wunused-macros -std=c89 -pedantic
#EXEC=myapp

ALL_C_FILES=$(wildcard *.c)
SOURCE_FILES=$(filter-out test_%.c, $(ALL_C_FILES))
OBJECT_FILES=$(SOURCE_FILES:.c=.o)
TEST_FILES=$(wildcard test_*.c)
ADDITIONAL_SOURCE_FILES = $(shell for file in $(SOURCE_FILES); do \
	if ! grep -q 'int main' $$file; then echo $$file; fi; \
done)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

run-tests: $(TEST_FILES) $(OBJECT_FILES)
	mkdir -p bin
	$(CC) -o bin/test_properties4c $^ $(CFLAGS)
	./bin/test_properties4c

.PHONY: clean

clean:
	rm -f *.o
	rm -f *.out
	rm -rf bin
