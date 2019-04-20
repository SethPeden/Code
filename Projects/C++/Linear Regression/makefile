CPP:= g++ -std=c++17
MAIN:= main.cpp
EXEC:= main
INCLUDES:= -I/vector.hpp
DEPENDENCIES:= vector.hpp
RM:= rm -r

all: ${DEPENDENCIES}
	${CPP} ${MAIN} ${INCLUDES} -o ${EXEC}

clean:
	${RM} ${EXEC}
