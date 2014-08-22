# CXX=g++
# CXXFLAGS=-c
# LDFLAGS=
# SOURCES=game.cpp
# OBJECTS=$(SOURCES:.cpp=.o)
# EXECUTABLE=game.out

# all: $(SOURCES) $(EXECUTABLE)

# $(EXECUTABLE): $(OBJECTS)
# 	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

# .cpp.o:
# 	$(CXX) $(CXXFLAGS) $< -o $@

# clean:
# 	rm *.o *.out

CXX=g++
CXXFLAGS=-O3
TARGET=$(shell basename `pwd`)
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)

all: $(TARGET)

$(OBJECTS): $(SOURCES)

$(TARGET): $(OBJECTS)
	$(CXX) -o $(TARGET) $(CXXFLAGS) $(OBJECTS)

clean:
	$(RM) $(OBJECTS) $(TARGET)

.PHONY: all clean