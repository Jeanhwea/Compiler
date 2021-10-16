TARGET_EXEC ?= compiler

BLD_DIR ?= ./build
SRC_DIR ?= ./src

SRCS := $(shell find $(SRC_DIR) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BLD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS  := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS  ?= $(INC_FLAGS) -MMD -MP

$(BLD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# assembly
$(BLD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BLD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BLD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BLD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
