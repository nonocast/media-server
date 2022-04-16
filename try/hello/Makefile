# https://stackoverflow.com/questions/30573481/how-to-write-a-makefile-with-separate-source-and-header-directories/30602701#30602701

CC := clang++
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := build

EXE := $(BIN_DIR)/app
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CCFLAG := -std=c++11 -arch x86_64
# CCFLAG := -std=c++11 -arch arm64
CPPFLAGS := -Iinclude
CFLAGS   := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(CCFLAG) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CCFLAG) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

run:
	./build/app

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

# -include $(OBJ:.o=.d)