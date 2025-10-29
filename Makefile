.PHONY: clean

TESTS_DIR=./tests
SRC_DIR=./src
INCLUDE_DIR=./include
OBJ_DIR=./obj
EXEC_DIR=./exec

CXX = g++
CXXFLAGS = -Wall -std=c++17 -O3

# Executables
TARGETS = $(EXEC_DIR)/slm # $(EXEC_DIR)/char_seq_unittest

# Default target
all: $(TARGETS)

slm: $(EXEC_DIR)/slm

# tests: $(EXEC_DIR)/char_seq_unittest

# $(EXEC_DIR)/char_seq_unittest: $(OBJ_DIR)/char_seq_unittest.o $(OBJ_DIR)/char_seq.o
# 	$(CXX)  $(CXXFLAGS) $^ -o $@

$(EXEC_DIR)/slm: $(OBJ_DIR)/main.o $(OBJ_DIR)/kgrams.o $(OBJ_DIR)/char_seq.o $(OBJ_DIR)/tokenizer.o $(OBJ_DIR)/utils.o
	$(CXX)  $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX)  $(CXXFLAGS) -c $(SRC_DIR)/main.cpp -o $@

$(OBJ_DIR)/kgrams.o: $(SRC_DIR)/kgrams.cpp $(INCLUDE_DIR)/kgrams.h
	$(CXX)  $(CXXFLAGS) -c $(SRC_DIR)/kgrams.cpp -o $@

# $(OBJ_DIR)/char_seq_unittest.o: $(TESTS_DIR)/char_seq_unittest.cpp
# 	$(CXX)  $(CXXFLAGS) -c $(TESTS_DIR)/char_seq_unittest.cpp -o $@

$(OBJ_DIR)/char_seq.o: $(SRC_DIR)/char_seq.cpp $(INCLUDE_DIR)/char_seq.h
	$(CXX)  $(CXXFLAGS) -c $(SRC_DIR)/char_seq.cpp -o $@

$(OBJ_DIR)/tokenizer.o: $(SRC_DIR)/tokenizer.cpp $(INCLUDE_DIR)/tokenizer.h
	$(CXX)  $(CXXFLAGS) -c $(SRC_DIR)/tokenizer.cpp -o $@

$(OBJ_DIR)/utils.o: $(SRC_DIR)/utils.cpp $(INCLUDE_DIR)/utils.h
	$(CXX)  $(CXXFLAGS) -c $(SRC_DIR)/utils.cpp -o $@

clean:
	rm -f $(OBJ_DIR)/*.o

deepclean:
	rm -f $(OBJ_DIR)/*.o
	rm $(EXEC_DIR)/*
