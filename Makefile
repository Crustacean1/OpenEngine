

headers := ${wildcard */*/*/*.h} ${wildcard */*/*.h} ${wildcard */*.h}
sources := ${wildcard */*/*/*.c*} ${wildcard */*/*.c*} ${wildcard */*.c*} main.cpp

cppobjs := ${wildcard */*/*/*.cpp} ${wildcard */*/*.cpp} ${wildcard */*.cpp} main.cpp
cppobjs := ${cppobjs:%.cpp=%.o}

objects:=  ${sources}
objects:= ${objects:%.cpp=%.o}
objects:= ${objects:%.c=%.o}

target := $(shell pwd | xargs basename)

.PHONY = test prep clean %.h

${target}: ${objects}
	g++ -o ${target} ${objects} -g -std=c++20 -L/home/kamil2/Libraries/glfw-3.3.2/build/src -lglfw3 -lrt -lm -ldl -lX11 -lpthread -lGL

%.o: %.cpp ${headers}
	g++ -g -I/home/kamil2/Libraries/glfw-3.3.2/include/ -I/home/kamil2/Libraries/GLAD/ -I/home/kamil2/Libraries/glm -std=c++20 -c $< -o ${subst cpp,o,$<}

%.h: %.cpp
	touch ${subst cpp,h,$<}

test:
	@echo obj targets: ${objects}
prep:
	clear
clean:
	rm -f ${cppobjs}