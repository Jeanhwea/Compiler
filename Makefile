TARGET   := pl0c

BLD_DIR  := output
INC_DIR  := include
SRC_DIR  := source
TEST_DIR := test

SRCS     := $(shell find $(SRC_DIR) -name *.c)
OBJS     := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS     := $(OBJS:.o=.d)
SRCS2    := $(shell find $(TEST_DIR) -name *.c)
OBJS2    := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS2    := $(OBJS:.o=.d)


CC       := gcc
CCFLAGS  := -I$(INC_DIR) -g -MMD -MP
LDFLAGS  := -I$(INC_DIR) -g

all: $(BLD_DIR)/$(TARGET)
	cp $(BLD_DIR)/$(TARGET) .


# target
$(BLD_DIR)/$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# c source
$(BLD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@

# tests
$(BLD_DIR)/%.test: $(OBJS) $(BLD_DIR)/%.c.o
	$(CC) $(LDFLAGS) $(OBJS) $(BLD_DIR)/%.c.o -o $@


setup: clean index
	bear -- make

index: clean
	find $(INC_DIR) $(SRC_DIR) -type f | sort > cscope.files
	cscope -bqk
	ctags -e -L cscope.files

-include $(DEPS)

.PHONY: all clean index setup
clean:
	$(RM) -r $(BLD_DIR) pl0c cscope.* compile_commands.json
