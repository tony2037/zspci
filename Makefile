CFLAGS = -g

BINS = zspci
SRCS = $(shell echo *.c)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BINS)

$(BINS): $(OBJS)
		$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
		$(CC) -c $< -o $@ $(CFLAGS) $(LD_FLAGS)

clean:
		/bin/rm -f *.o *~ $(BINS)
