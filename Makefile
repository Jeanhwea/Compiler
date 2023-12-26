# global
TARGET   := pcc
BLD_DIR  := output
INC_DIR  := include
SRC_DIR  := source
BIN_DIR  := bin
TOOL_DIR := tool
# source codes
SRCS     := $(shell find $(SRC_DIR) -name *.c)
OBJS     := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS     := $(OBJS:.o=.d)
# tools
TSRCS    := $(shell find $(TOOL_DIR) -name *.c)
TOBJS    := $(filter-out $(BLD_DIR)/$(SRC_DIR)/main.c.o,$(OBJS))
TDEPS    := $(TOBJS:.o=.d)
TOOLS    := $(TSRCS:$(TOOL_DIR)/%.c=$(BIN_DIR)/%)
# build config
CC       := gcc
DEBUG    := -g
CCFLAGS  := -I$(INC_DIR) $(DEBUG) -MMD -MP
LDFLAGS  := -I$(INC_DIR) $(DEBUG)

# all build targets
all: $(TARGET) $(TOOLS)


# target
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

# c source
$(BLD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c $< -o $@
# tools
$(BIN_DIR)/%: $(TOBJS) $(BLD_DIR)/$(TOOL_DIR)/%.c.o
	$(CC) $(LDFLAGS) $^ -o $@

# include dependencies
-include $(DEPS)

setup: clean index
	bear -- make

index: clean
	find $(INC_DIR) $(SRC_DIR) -type f | sort > cscope.files
	cscope -bqk
	ctags -e -L cscope.files

clean:
	$(RM) -r $(BLD_DIR) $(TARGET) bin/* viz*
	find . -iname "*.o" -or -iname "*.s" -or -iname "*.run" | xargs -I {} rm -f {}
	find . -iname "core*" | xargs -I {} rm -f {}

distclean:
	$(RM) -r compile_commands.json cscope.* TAGS

.PHONY: all clean distclean index setup
