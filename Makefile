CXX = g++
CPPFLAGS = -std=c++11 -Wall
FILES = 50231.o hash-table.o result.o tower.o

main: $(FILES)
	$(CXX) $(CPPFLAGS) $(FILES) -o main