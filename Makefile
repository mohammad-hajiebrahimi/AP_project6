CC_EXEC= g++
CC_FLAGS= -c

CC= ${CC_EXEC} ${CC_FLAGS}
BUILD_DIR= build
SRC_DIR= src

${BUILD_DIR}/a.out: ${BUILD_DIR}/main.o
	g++ ${BUILD_DIR}/main.o -o ${BUILD_DIR}/a.out

${BUILD_DIR}/main.o: main.cpp ${SRC_DIR}/bmp.cpp ${SRC_DIR}/bmp.hpp
	g++ -c main.cpp -o ${BUILD_DIR}/main.o

clean:
	rm ${BUILD_DIR}/*.o ${BUILD_DIR}/a.out

run:
	${BUILD_DIR}/./a.out -B -S 3:4:30:40 -G
