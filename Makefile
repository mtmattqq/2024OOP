CXX = g++
CPPFLAGS = -std=c++11 -Wall
FILES = 50231.o hash-table.o

main: $(FILES)
	$(CXX) $(CPPFLAGS) $(FILES) -o main