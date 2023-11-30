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

all: $(BLD_DIR)/$(TARGET)
	cp $(BLD_DIR)/$(TARGET) .

# target
$(BLD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# c source
$(BLD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

setup: clean index
	bear -- make

index: clean
	find inc src -type f | sort > cscope.files
	cscope -bqk
	ctags -e -L cscope.files

-include $(DEPS)

.PHONY: all clean index setup
clean:
	$(RM) -r $(BLD_DIR) pl0c cscope.* compile_commands.json
