DEMO1_DIR=$(shell pwd)

DEMO1_COMMON_SRC_FILES=$(wildcard $(DEMO1_DIR)/common/*.cpp)
DEMO1_COMMON_OBJ_FILES=$(DEMO1_COMMON_SRC_FILES:%.cpp=%.o)

CXXFLAGS=-std=c++11 -Wall -I$(DEMO1_DIR)/common
LDLIBS=-lboost_system -lboost_thread -pthread -lboost_serialization

all: demo1_server demo1_client 

demo1_server: server/demo1_server.o $(DEMO1_COMMON_OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

demo1_client: client/demo1_client.o $(DEMO1_COMMON_OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

clean:
	rm -rf demo1_client demo1_server
	find $(DEMO1_DIR) -name *.o -delete
