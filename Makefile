CXX = g++
CXXFLAGS = -Wall -g

HEADERS = $(wildcard Financial/*.hpp)
SOURCES = $(wildcard Financial/*.cpp) test.cpp

all: fss_test

fss_test: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o fss_test $(SOURCES)

test: fss_test
	./fss_test

clean:
	rm -f fss_test
