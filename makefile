TARGET = game
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRC = $(filter-out $(SRC_DIR)/test.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I$(INC_DIR)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET) tests

run: all
	./$(TARGET)

# tests
run_tests:
	g++ -Wall -Wextra -std=c++17 -Iinclude src/test.cpp obj/*.o -o tests && ./tests

