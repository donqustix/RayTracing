LIBNAME = RayTracing
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra
LDFLAGS =
LDLIBS = bin/$(LIBNAME).a
SRCS = $(filter-out src/main.cpp, $(wildcard src/*.cpp))
OBJS = $(addprefix bin/, $(notdir $(SRCS:.cpp=.o)))

$(LIBNAME): $(OBJS)
	ar rvs $(LDLIBS) $(OBJS)

test: src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp -o bin/Test $(LDLIBS) $(LDFLAGS)

bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

