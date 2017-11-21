CXX = g++
RM = rm
ECHO = echo

CXXFLAGS = -g -O0 -std=c++11 -Wall -Werror -pthread
INCLUDES = -I.  -I${ROOT}/common/third_party/include/
LDFLAGS = ${ROOT}/common/third_party/lib/libgtest.a

MAIN_SRC = main.cpp
MAIN_OBJ = ${MAIN_SRC:.cpp=.o}
SRCS = $(filter-out ${MAIN_SRC}, $(wildcard *.cpp))
OBJS = $(SRCS:.cpp=.o)

all : ${BINARY}

${BINARY} : ${MAIN_OBJ} ${OBJS}
	${CXX} -o $@ ${MAIN_OBJ} ${OBJS} ${LDFLAGS}

%.o : %.cpp
	${CXX} -c -o $@ ${CXXFLAGS} $*.cpp ${INCLUDES}

clean:
	-${RM} -rf ${MAIN_OBJ} ${OBJS} ${BINARY}

