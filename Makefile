CC = g++
# CC = clang++
# CC_FLAGS = -Wall -Werror -g
CC_FLAGS = -g
SRC_CPP = $(shell find src/ -name '*.cc')
CC_LINK = -lreadline -lboost_filesystem -lboost_serialization -lboost_system -lboost_regex
BUILD = bin/minidb

all:
	$(CC) $(CC_FLAGS) $(SRC_CPP) $(CC_LINK) -o $(BUILD)