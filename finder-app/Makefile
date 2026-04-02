CROSS_COMPILE ?=

CC := $(CROSS_COMPILE)gcc
CFLAGS := -Wall -o2

TARGET := writer

SRCS := writer.c
OBJS := $(SRCS: .c=.o)

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS) $(TARGET)
