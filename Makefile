CXX=g++

CXXFLAGS = -std=c++11 -Wall -Wextra -Wno-unused-parameter -Wno-unused-private-field

main: main.o TST.o
	$(CXX) $(CXXFLAGS) -o main main.o TST.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp
	
clean:
	del -f ${BINARIES} *.o *.exe *.gch
