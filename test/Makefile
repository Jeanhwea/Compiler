CC   := ../pl0c

SRCS := $(wildcard *.pas)
RUNS := $(SRCS:%.pas=%.run)

all: $(RUNS)

%.run: %.pas
	$(CC) $<
	rm *.o

clean:
	-rm *.s *.o *.run
