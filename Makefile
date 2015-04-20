# Makefile for kt project.
# Author: Laurent Stacul

# Global settings
CC=g++
CFLAGS=-Wall -Werror -Wpedantic -Wextra -std=c++11 -O -g
LDFLAGS=

# Dependencies
# BOOST=program_options log log_setup thread date_time filesystem system unit_test_framework
# DLIBS=$(foreach libname, $(BOOST),boost_$(libname)-mt)

# Source code
SRC_DIR=src

MAIN_OBJ=$(SRC_DIR)/ClientMain.o

SRC:=$(shell find $(SRC_DIR) -name "*.cpp")
HEADERS:=$(shell find $(SRC_DIR) -name "*.h")
OBJ:=$(patsubst %.cpp, %.o, $(SRC))
EXEC=chatroom_srv

all: $(EXEC)

build: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(foreach libname, $(DLIBS),-l$(libname)) -o $@ $^ $(LDFLAGS)

%.o: %.cpp $(HEADERS)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	find . -name *.o -exec rm -f {} \;
	rm -f $(EXEC)
	rm -f core

.PHONY: all debug build build-test run-test
