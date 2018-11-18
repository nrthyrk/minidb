# CC = g++
CC = clang++
# CC_FLAGS = -Wall -Werror -g
CC_FLAGS = -g
SRC_CC = $(shell find src/ -name '*.cc')
MAIN = src/main.cpp
EXAMPLE = src/example.cpp
BOOST_LINK = -lboost_filesystem -lboost_serialization -lboost_system -lboost_regex
BUILD = bin/minidb
BUILD_EG = bin/example

executable:
	$(CC) $(CC_FLAGS) $(SRC_CC) $(MAIN) $(BOOST_LINK) -lreadline -o $(BUILD)

example:
	$(CC) $(CC_FLAGS) $(SRC_CC) $(EXAMPLE) $(BOOST_LINK) -o $(BUILD_EG)