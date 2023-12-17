CC_EXEC= g++
CC_FLAGS= -c

CC= ${CC_EXEC} ${CC_FLAGS}
BUILD_DIR= build
SRC_DIR= src

ImageEditor.out: ${BUILD_DIR}/main.o ${BUILD_DIR}/bmp.o
	g++ ${BUILD_DIR}/main.o -o ImageEditor.out

${BUILD_DIR}/main.o: main.cpp ${SRC_DIR}/bmp.cpp ${SRC_DIR}/bmp.hpp ${SRC_DIR}/ColorFilter.cpp ${SRC_DIR}/ColorFilter.hpp ${SRC_DIR}/Filters.cpp ${SRC_DIR}/Filters.hpp ${SRC_DIR}/KernelFilter.cpp ${SRC_DIR}/KernelFilter.hpp
	g++ -c main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/bmp.o:${SRC_DIR}/bmp.cpp ${SRC_DIR}/bmp.hpp
	g++ -c ${SRC_DIR}/bmp.cpp -o ${BUILD_DIR}/bmp.o

clean:
	rm ${BUILD_DIR}/*.o ImageEditor.out

run:
	./ImageEditor.out -B -E -S -I -G
