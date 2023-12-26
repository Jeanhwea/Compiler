CC   := ../pc

SRCS := $(wildcard *.pas)
RUNS := $(SRCS:%.pas=%.run)

all: $(RUNS)

%.run: %.pas
	$(CC) $<

clean:
	-rm -f *.s *.o *.run
