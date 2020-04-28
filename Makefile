CC ?= gcc

BUILD_DIR=./build
INC_DIR=./inc
SRC_DIR=./src
DEMO_DIR=./demo
TEST_DIR=./tests

DEMO_APP=$(BUILD_DIR)/klein-demo
DEMO_FILES=$(DEMO_DIR)/demo.c
DEMO_OBJS=$(DEMO_FILES:.c=.o)

KLEIN_FILES=$(SRC_DIR)/simple-klein.c $(SRC_DIR)/internals.c
KLEIN_OBJS=$(KLEIN_FILES:.c=.o)

TEST_FILES=$(TEST_DIR)/test-vectors.c $(TEST_DIR)/main.c
TEST_OBJS=$(TEST_FILES:.c=.o)
TEST_BINARY=$(BUILD_DIR)/klein-tests

CFLAGS = -std=c99 -I$(INC_DIR)

.PHONY: default clean debug demo tests

default: demo

demo: $(DEMO_APP)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(DEMO_OBJS) $(KLEIN_OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DEMO_APP): $(BUILD_DIR) $(KLEIN_OBJS) $(DEMO_OBJS)
	gcc $(KLEIN_OBJS) $(DEMO_OBJS) -o $(DEMO_APP)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST_BINARY): $(BUILD_DIR) $(KLEIN_OBJS) $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(KLEIN_OBJS) -o $(TEST_BINARY)
	$(TEST_BINARY)

tests: CFLAGS+=-I$(TEST_DIR)
tests: $(TEST_BINARY)

debug: CFLAGS+=-g -DDEBUG
debug: default
