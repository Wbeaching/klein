CC ?= gcc

BUILD_DIR=./build
INC_DIR=./inc
SRC_DIR=./src
DEMO_DIR=./demo

DEMO_APP=$(BUILD_DIR)/klein-demo
DEMO_FILES=$(DEMO_DIR)/demo.c
DEMO_OBJS=$(DEMO_FILES:.c=.o)

KLEIN_FILES=$(SRC_DIR)/simple-klein.c $(SRC_DIR)/internals.c
KLEIN_OBJS=$(KLEIN_FILES:.c=.o)

CFLAGS = -std=c99 -I$(INC_DIR)

.PHONY: default clean debug

default: $(DEMO_APP)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(DEMO_OBJS) $(KLEIN_OBJS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(DEMO_APP): $(BUILD_DIR) $(KLEIN_OBJS) $(DEMO_OBJS)
	gcc $(KLEIN_OBJS) $(DEMO_OBJS) -o $(DEMO_APP)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

debug: CFLAGS+=-g
debug: default
