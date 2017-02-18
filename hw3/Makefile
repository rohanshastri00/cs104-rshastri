# Rohan Shastri
# CS104: Spring 2017
# Makefile to run and compile tests for HW3

# Compiler info
CXX = g++
CPPFLAGS = -g -Wall
GTEST = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread
BIN_DIR = bin

cnfeval: cnf.cpp cnf.h

cnf.o: cnfeval.cpp cnf.o
	$(CXX) $(CPPFLAGS) -c cnfeval.cpp -o cnfeval

scheduling: scheduling.cpp queueint.o
	$(CXX) $(CPPFLAGS) queueint.o llistint.o scheduling.cpp -o scheduling

queueint.o: queueint.h queueint.cpp
	$(CXX) $(CPPFLAGS) -c queueint.cpp -o queueint.o

llisttest: llisttest.cpp llistint.o
	$(CXX) $(CPPFLAGS) $^ $(GTEST) -o $@


llistint.o: llistint.h llistint.cpp 
	$(CXX) $(CPPFLAGS) -c llistint.cpp -o llistint.o 




.PHONY: clean


clean:
	rm -rf $(BIN_DIR)
	rm -rf queueint.o
	rm -rf llisttest
	rm -rf llistint.o
	rm -rf scheduling
	rm -rf cnf.o
	rm -rf cnfeval

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp







