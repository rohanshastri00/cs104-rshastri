CXX=g++
CXXFLAGS=-g -Wall 

all: puzzle 

#heap.o: heap.cpp heap.h
#	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c heap.cpp
puzzle: puzzle.o board.o puzzle_move.o puzzle_heur.o puzzle_solver.o heap.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ puzzle.o board.o puzzle_move.o puzzle_heur.o puzzle_solver.o
puzzle.o: puzzle.cpp board.h puzzle_heur.h puzzle_solver.h
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle.cpp
board.o: board.cpp board.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c board.cpp
puzzle_heur.o: puzzle_heur.cpp puzzle_heur.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_heur.cpp
puzzle_move.o: puzzle_move.cpp puzzle_move.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_move.cpp
puzzle_solver.o: puzzle_solver.cpp puzzle_solver.h 
	$(CXX) $(CXXFLAGS) $(DEFS) -o $@ -c puzzle_solver.cpp

clean:
	rm -f *.o heap
	rm -f *.o puzzle