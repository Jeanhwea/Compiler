BLD_DIR  := output
INC_DIR  := include
SRC_DIR  := source
BIN_DIR  := bin
TEST_DIR := tests

SRCS     := $(shell find $(SRC_DIR) -name *.c)
OBJS     := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS     := $(OBJS:.o=.d)
TARGET   := pl0c

TSRCS    := $(shell find $(TEST_DIR) -name *.c)
TOBJS    := $(filter-out $(BLD_DIR)/$(SRC_DIR)/main.c.o,$(OBJS))
TDEPS    := $(TOBJS:.o=.d)
TESTS    := $(TSRCS:$(TEST_DIR)/%.c=$(BIN_DIR)/%.test)


CC       := gcc
CCFLAGS  := -I$(INC_DIR) -g -MMD -MP
LDFLAGS  := -I$(INC_DIR) -g

all: $(TARGET) $(TESTS)


# target
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# unit test
$(BIN_DIR)/%.test: $(TOBJS) $(BLD_DIR)/$(TEST_DIR)/%.c.o
	$(CC) $(LDFLAGS) $^ -o $@

# c source
$(BLD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@


setup: clean index
	bear -- make

index: clean
	find $(INC_DIR) $(SRC_DIR) -type f | sort > cscope.files
	cscope -bqk
	ctags -e -L cscope.files

-include $(DEPS)

.PHONY: all clean distclean index setup tests
clean:
	$(RM) -r $(BLD_DIR) pl0c bin/* viz*
distclean:
	$(RM) -r compile_commands.json cscope.* TAGS
