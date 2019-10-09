#
# Makefile para programas exemplo
# 

CC=gcc
LIB_DIR=../lib

all: exemplo mandel teste_vetor series multiThreads filosofos barbeiro schedulerTest

exemplo: exemplo.c $(LIB_DIR)/libcthread.a
	$(CC) -o exemplo exemplo.c -L$(LIB_DIR) -lcthread -Wall

teste_vetor: teste_vetor.c $(LIB_DIR)/libcthread.a
	$(CC) -o teste_vetor teste_vetor.c -L$(LIB_DIR) -lcthread -Wall

mandel: mandel.c $(LIB_DIR)/libcthread.a
	$(CC) -o mandel mandel.c -L$(LIB_DIR) -lcthread -lm -Wall

series: series.c $(LIB_DIR)/libcthread.a
	$(CC) -o series series.c -L$(LIB_DIR) -lcthread -lm -Wall

multiThreads: multiThreads.c $(LIB_DIR)/libcthread.a
	$(CC) -o multiThreads multiThreads.c -L$(LIB_DIR) -lcthread -Wall

filosofos: filosofos.c $(LIB_DIR)/libcthread.a
	$(CC) -o filosofos filosofos.c -L$(LIB_DIR) -lcthread -Wall

barbeiro: barbeiro.c $(LIB_DIR)/libcthread.a
	$(CC) -o barbeiro barbeiro.c -L$(LIB_DIR) -lcthread -Wall

schedulerTest: schedulerTest.c $(LIB_DIR)/libcthread.a
	$(CC) -o schedulerTest schedulerTest.c -L$(LIB_DIR) -lcthread -Wall

clean:
	rm -rf exemplo mandel teste_vetor series multiThreads filosofos barbeiro schedulerTest *.o *~
