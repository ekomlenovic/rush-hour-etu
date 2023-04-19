CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic -Werror -ggdb -std=c++20
CPPFLAGS = -I$(SRC_DIR)
LDFLAGS =
SRC_DIR = src
OBJ_DIR = obj
EXEC_DIR = bin
MAIN_EXEC = $(EXEC_DIR)/main
TEST_EXEC = $(EXEC_DIR)/test
DOXYFILE = doc/image.doxy

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SRCS = $(filter-out $(SRC_DIR)/main_test.cpp, $(SRCS))
TEST_SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(SRCS))
MAIN_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(MAIN_SRCS))
TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TEST_SRCS))
MAIN_DEPS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.d,$(MAIN_SRCS))
TEST_DEPS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.d,$(TEST_SRCS))

CPPFLAGS = -I$(SRC_DIR)
LDFLAGS =
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -ggdb -O0 -DDEBUG
COMMON_FLAGS = -Wall -Wextra -Wpedantic -Werror -std=c++20


all: main test

release: CXXFLAGS = $(COMMON_FLAGS) $(RELEASE_FLAGS)
release: clean all

debug: CXXFLAGS = $(COMMON_FLAGS) $(DEBUG_FLAGS)
debug: clean all

main: $(MAIN_EXEC)

test: $(TEST_EXEC)

$(MAIN_EXEC): $(MAIN_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

-include $(MAIN_DEPS)
-include $(TEST_DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(MAIN_DEPS) $(TEST_DEPS) $(MAIN_EXEC) $(TEST_EXEC) export/BFS*/*.svg map/BFS*/*.txt

.PHONY: doxy
doxy:
	doxygen $(DOXYFILE)

.PHONY: clean doxy
cleandoxy:
	rm -rf ./doc/html/*.* ./doc/html/search ./doc/latex/*.* ./doc/latex/Makefile

