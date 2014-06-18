NAME := 2048

CXX := g++
CXXFLAGS := -O2

SOURCE_FILES := $(wildcard *.cpp)
SOURCE_OBJECTS := $(SOURCE_FILES:%.cpp=%.o)

all: $(NAME)
$(NAME):
	$(CXX) $(CXXFLAGS) $(SOURCE_FILES) -o $(NAME)

clean:
	rm -f $(NAME)
