CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

SRC = $(filter-out $(SRC_DIR)/main.cpp $(SRC_DIR)/main_jeu.cpp $(SRC_DIR)/test.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

EXEC_MAIN = game_auto
EXEC_MANUAL = game_manual
EXEC_TEST = tests

all: $(EXEC_MAIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(EXEC_MAIN): $(OBJ) $(OBJ_DIR)/main.o
	$(CXX) $(OBJ) $(OBJ_DIR)/main.o -o $(EXEC_MAIN)
run_auto: $(EXEC_MAIN)
	./$(EXEC_MAIN)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC_MANUAL): $(OBJ) $(OBJ_DIR)/main_jeu.o
	$(CXX) $(OBJ) $(OBJ_DIR)/main_jeu.o -o $(EXEC_MANUAL)
run_manual: $(EXEC_MANUAL)
	./$(EXEC_MANUAL)

$(OBJ_DIR)/main_jeu.o: $(SRC_DIR)/main_jeu.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXEC_TEST): $(OBJ) $(OBJ_DIR)/test.o
	$(CXX) $(OBJ) $(OBJ_DIR)/test.o -o $(EXEC_TEST)
run_tests: $(EXEC_TEST)
	./$(EXEC_TEST)

$(OBJ_DIR)/test.o: $(SRC_DIR)/test.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(EXEC_MAIN) $(EXEC_MANUAL) $(EXEC_TEST)

.PHONY: all run_auto run_manual run_tests clean