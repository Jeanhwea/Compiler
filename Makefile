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

setup: clean
	bear -- make
	find inc src -type f | sort > cscope.files
	cscope -bqk
	ctags  -e -L cscope.files

-include $(DEPS)

.PHONY: clean setup
clean:
	$(RM) -r $(BLD_DIR) cscope.*
