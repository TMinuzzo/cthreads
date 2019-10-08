#
# Makefile para programas exemplo
# 

CC=gcc
LIB_DIR=../lib

all: exemplo mandel teste_vetor series multiThreads filosofos barbeiro

exemplo: exemplo.c $(LIB_DIR)/libcthread.a
	$(CC) -m32 -o exemplo exemplo.c -L$(LIB_DIR) -lcthread -Wall

teste_vetor: teste_vetor.c $(LIB_DIR)/libcthread.a
	$(CC) -m32 -o teste_vetor teste_vetor.c -L$(LIB_DIR) -lcthread -Wall

mandel: mandel.c $(LIB_DIR)/libcthread.a
	$(CC) -m32 -o mandel mandel.c -L$(LIB_DIR) -lcthread -lm -Wall

series: series.c $(LIB_DIR)/libcthread.a
	$(CC) -m32 -o series series.c -L$(LIB_DIR) -lcthread -lm -Wall

multiThreads: multiThreads.c $(LIB_DIR)/libcthread.a
	$(CC) -m32 -o multiThreads multiThreads.c -L$(LIB_DIR) -lcthread -Wall

filosofos: filosofos.c $(LIB_DIR)/libcthread.a
	$(CC) -m32 -o filosofos filosofos.c -L$(LIB_DIR) -lcthread -Wall

barbeiro: barbeiro.c $(LIB_DIR)/libcthread.a
	$(CC) -m32 -o barbeiro barbeiro.c -L$(LIB_DIR) -lcthread -Wall

clean:
	rm -rf exemplo mandel teste_vetor series multiThreads filosofos barbeiro *.o *~
