TARGET  ?= pl0c

BLD_DIR ?= out
INC_DIR ?= inc
SRC_DIR ?= src

SRCS    := $(shell find $(SRC_DIR) -name *.c)
OBJS    := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS    := $(OBJS:.o=.d)


CC      := gcc
CCFLAGS ?= -I$(INC_DIR) -g -MMD -MP
LDFLAGS ?= -I$(INC_DIR) -g

# target
$(BLD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BLD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BLD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
