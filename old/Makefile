TINYRCPP_DIR=TODO

TINYRCPP_SRC_FILES=$(wildcard $(TINYRCPP_DIR)/src/*.cpp)
TINYRCPP_OBJECT_FILES=$(TINYRCPP_SRC_FILES:%.cpp=%.o)

CXXFLAGS=-std=c++11 -Wall -I$(TINYRCPP_DIR)/include -lboost_system -lboost_thread -pthread
