DIR_INC=./include
DIR_SRC=./source
DIR_OBJ=./obj
DIR_BIN=./bin

SRC=$(wildcard ${DIR_SRC}/*.cpp)  
OBJ=$(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET_SERVER=server
TARGET_CLIENT=client
BIN_TARGET_SERVICE=./${TARGET_SERVER}
BIN_TARGET_CLIENT=./${TARGET_CLIENT}

CC=g++
CFLAGS=-g -Wall -I ${DIR_INC}

server:${OBJ}
	$(CC) $(OBJ)  -o $@
    
${BIN_TARGET_CLIENT}:${OBJ}
	$(CC) $(OBJ)  -o $@    
    
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c  $^ -o $@
.PHONY:clean
clean:
	rm ${DIR_OBJ}/*.o
	rm ./*
