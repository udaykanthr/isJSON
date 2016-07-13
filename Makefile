src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lm

isjson: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) isjson
