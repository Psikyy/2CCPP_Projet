TARGET = test_plateau

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SRC = $(SRC_DIR)/main.cpp $(SRC_DIR)/Plateau.cpp

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
	rm -rf $(OBJ_DIR) $(TARGET)

run: all
	./$(TARGET)
