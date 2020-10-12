CXX=g++

CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

main: main.o TST.o
	$(CXX) $(CXXFLAGS) -o project1.out main.o TST.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
	
clean:
	rm -f ${BINARIES} *.o *.exe *.gch *.out
