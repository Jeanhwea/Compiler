CC   := fpc

SRCS := $(wildcard *.pas)
RUNS := $(SRCS:%.pas=%.run)

all: $(RUNS)

%.run: %.pas
	$(CC) -o$@ $<

clean:
	-rm -f *.s *.o *.run
