#
# Makefile de EXEMPLO
#
# OBRIGATÓRIO ter uma regra "all" para geração da biblioteca e de uma
# regra "clean" para remover todos os objetos gerados.
#
# É NECESSARIO ADAPTAR ESSE ARQUIVO de makefile para suas necessidades.
#  1. Cuidado com a regra "clean" para não apagar o "support.o"
#
# OBSERVAR que as variáveis de ambiente consideram que o Makefile está no diretótio "cthread"
# 

CC=gcc
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src

all: scheduler cthread thread
	mkdir -p lib
	ar crs $(LIB_DIR)/libcthread.a $(BIN_DIR)/scheduler.o $(BIN_DIR)/lib.o $(BIN_DIR)/support.o $(BIN_DIR)/thread.o

scheduler:
	$(CC) -c $(SRC_DIR)/scheduler.c -o $(BIN_DIR)/scheduler.o -Wall

cthread:
	$(CC) -c $(SRC_DIR)/lib.c -o $(BIN_DIR)/lib.o -Wall

thread:
	$(CC) -c $(SRC_DIR)/thread.c -o $(BIN_DIR)/thread.o -Wall

clean:
	rm -rf $(LIB_DIR)/*.a $(BIN_DIR)/scheduler.o $(BIN_DIR)/thread.o $(BIN_DIR)/lib.o $(SRC_DIR)/*~ $(INC_DIR)/*~ *~
