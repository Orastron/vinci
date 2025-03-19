UNAME := $(shell uname -o)

ifeq ($(UNAME),GNU/Linux)
	VINCI_SRC    = vinci-xcb.c
	EXTRAOPTIONS = -lxcb
else ifeq ($(UNAME),Msys)
	VINCI_SRC    = vinci-win32.c
	EXTRAOPTIONS = -mwindows
else ifeq ($(UNAME),Darwin)
	VINCI_SRC    = vinci-cocoa.m
	EXTRAOPTIONS = -framework Cocoa -lobjc
endif

CC = gcc
CFLAGS = -std=c99 -O3
STRICT = -Wall -Wextra -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -Wuninitialized -Wmissing-declarations

BUILD_DIR = build

all: $(BUILD_DIR)/test

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/test: test.c $(VINCI_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(STRICT) $(VINCI_SRC) test.c -o $@ $(EXTRAOPTIONS)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean