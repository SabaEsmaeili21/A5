CXX = g++
CXXFLAGS = -std=c++20 -g -Wall -Wextra -I./include 
SRCDIR = source
OBJDIR = object
BINDIR = .
EXECUTABLE = $(BINDIR)/UTGame
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(^) -o $(@)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(wildcard include/*.hpp)
	$(CXX) $(CXXFLAGS) -c $(<) -o $(@)

.PHONY: all clean

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)