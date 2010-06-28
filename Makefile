# This makefile compiles the project Knaspack_Problem
# Sebastian Kupny
# date: Lowoszow, 05-june-2010
#http://www.opussoftware.com/tutorial/TutMakefile.htm
PROJ = start  			# the name of the project

CXX=g++
CFLAGS=-Wall -g
OBJS=element.o knaspackProblem.o beesAlgorithm.o  start.o

$(PROJ): $(OBJS)
	$(CXX) $(LFLAGS) $^ -o $@

$(OBJS): %.o: %.cpp
	$(CXX) -c  $(CFLAGS) $< -o $@

.PHONY: all clean run

clean:
	rm start *.o
run:
	./$(PROJ)
