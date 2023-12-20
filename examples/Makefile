CC   := ../pl0c

SRCS := $(wildcard *.pas)
RUNS := $(SRCS:%.pas=%.run)

all: $(RUNS)

%.run: %.pas
	$(CC) $<

clean:
	-rm *.s *.o *.run
