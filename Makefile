CC ?= gcc

BUILD_DIR=./build
INC_DIR=./inc
SRC_DIR=./src
DEMO_DIR=./demo
TEST_DIR=./tests

DEMO_APP=$(BUILD_DIR)/sklein-demo
DEMO_FILES=$(DEMO_DIR)/demo.c
DEMO_OBJS=$(DEMO_FILES:.c=.o)

KLEIN_FILES=$(SRC_DIR)/simple-klein.c $(SRC_DIR)/internals.c
KLEIN_OBJS=$(KLEIN_FILES:.c=.o)

TEST_FILES=$(TEST_DIR)/test-vectors.c $(TEST_DIR)/main.c
TEST_OBJS=$(TEST_FILES:.c=.o)
TEST_BINARY=$(BUILD_DIR)/sklein-tests

LIBRARY_NAME=libsklein

CFLAGS=-std=c99 -I$(INC_DIR) -fPIC

.PHONY: all clean debug demo tests library

all: library demo

demo: $(DEMO_APP)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(DEMO_OBJS) $(KLEIN_OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DEMO_APP): $(BUILD_DIR)/$(LIBRARY_NAME).a $(DEMO_OBJS)
	gcc -L$(BUILD_DIR) $(DEMO_OBJS) -l:$(LIBRARY_NAME).a -o $(DEMO_APP)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_BINARY): $(BUILD_DIR) $(KLEIN_OBJS) $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(KLEIN_OBJS) -o $(TEST_BINARY)
	$(TEST_BINARY)

library: $(BUILD_DIR)/$(LIBRARY_NAME).a $(BUILD_DIR)/$(LIBRARY_NAME).so
	cp $(INC_DIR)/sklein.h $(BUILD_DIR)/

$(BUILD_DIR)/$(LIBRARY_NAME).a: $(BUILD_DIR) $(KLEIN_OBJS)
	ar rcs $@ $(KLEIN_OBJS)

$(BUILD_DIR)/$(LIBRARY_NAME).so: $(BUILD_DIR) $(KLEIN_OBJS)
	gcc -shared -o $@ $(KLEIN_OBJS)

tests: CFLAGS+=-I$(TEST_DIR)
tests: $(TEST_BINARY)

debug: CFLAGS+=-g -DDEBUG
debug: default
