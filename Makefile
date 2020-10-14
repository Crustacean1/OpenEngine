sources := $(wildcard *.cpp)
headers := ${wildcard *.h}
objects := $(sources:%.cpp=%.o)
target := $(shell pwd | xargs basename)

${target}: ${objects}
	g++  -o ${target} ${objects} -g -std=c++17 -L/home/kamil2/Libraries/glfw-3.3.2/build/src -lglfw3 -lrt -lm -ldl -lX11 -lpthread -lGL

%.o: %.cpp ${headers}
	g++ -g -I/home/kamil2/Libraries/glfw-3.3.2/include/ -I/home/kamil2/Libraries/GLAD/ -std=c++17 -c $<

clean:
	rm -f *.o