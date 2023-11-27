TARGET  := pl0c

BLD_DIR := out
INC_DIR := inc
SRC_DIR := src

SRCS    := $(shell find $(SRC_DIR) -name *.c)
OBJS    := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS    := $(OBJS:.o=.d)


CC      := gcc
CCFLAGS := -I$(INC_DIR) -g -MMD -MP
LDFLAGS := -I$(INC_DIR) -g

# target
$(BLD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# c source
$(BLD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@


-include $(DEPS)

.PHONY: clean
clean:
	$(RM) -r $(BLD_DIR)
