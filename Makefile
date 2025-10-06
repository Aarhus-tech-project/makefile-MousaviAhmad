CXX:=g++
AR:=ar
BUILD?=debug

INCLUDE_DIR:=include
SOURCE_DIR:=src
TEST_DIR:=tests
BUILD_DIR:=build
OBJ_DIR:=$(BUILD_DIR)/obj
LIB:=$(BUILD_DIR)/libclassics.a
APP:=$(BUILD_DIR)/app
TEST_BIN:=$(BUILD_DIR)/tests

CXXSTD:=-std=c++20
WARNINGS:=-Wall -Wextra -Wpedantic
INCLUDES:=-I$(INCLUDE_DIR)

ifeq ($(BUILD),release)
CXXFLAGS:=$(CXXSTD) $(WARNINGS) $(INCLUDES) -O2 -DNDEBUG -MMD -MP
else
CXXFLAGS:=$(CXXSTD) $(WARNINGS) $(INCLUDES) -Og -g -MMD -MP
endif

SRC:=$(wildcard $(SOURCE_DIR)/*.cpp)
OBJ:=$(patsubst $(SOURCE_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
DEPS:=$(OBJ:.o=.d)

LIB_OBJECTS:=$(OBJ_DIR)/hanoi.o $(OBJ_DIR)/bst.o

TEST_SRC:=$(TEST_DIR)/tests.cpp
TEST_OBJ:=$(OBJ_DIR)/tests.o
TEST_DEP:=$(TEST_OBJ:.o=.d)

.PHONY: all
all: $(LIB) $(APP) $(TEST_BIN)

$(LIB): $(LIB_OBJECTS)
	@mkdir -p $(dir $@)
	$(AR) rcs $@ $^

$(APP): $(filter-out $(LIB_OBJECTS),$(OBJ)) $(LIB)
	@mkdir -p $(dir $@)
	$(CXX) $^ -o $@

$(TEST_BIN): $(TEST_OBJ) $(LIB)
	@mkdir -p $(dir $@)
	$(CXX) $(TEST_OBJ) $(LIB) -o $@

$(TEST_OBJ): $(TEST_SRC)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run test clean debug release

run: $(APP)
	./$(APP) --hanoi 10

test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)

debug:
	$(MAKE) BUILD=debug

release:
	$(MAKE) clean
	$(MAKE) BUILD=release

-include $(DEPS) $(TEST_DEP)
