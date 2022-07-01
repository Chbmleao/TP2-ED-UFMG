#
# Copyright 2021 Alysson Ribeiro da Silva - Federal University of Minas Gerais
#
# Permission is hereby granted, free of charge, to any person obtaining a copy 
# of this software and associated documentation files (the "Software"), to deal 
# in the Software without restriction, including without limitation the rights 
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
# of the Software, and to permit persons to whom the Software is furnished to do 
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all 
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
# INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
# HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#

# cc and flags
CC = g++
CXXFLAGS = -pg -std=c++11 -g -Wall
#CXXFLAGS = -pg -std=c++11 -g -Wall

# folders
INCLUDE_FOLDER = ./include/
BIN_FOLDER = ./bin/
OBJ_FOLDER = ./obj/
SRC_FOLDER = ./src/
ASSETS = ./assets/
OUT_FOLDER = ./out/

# all sources, objs, and header files
MAIN = Main
TARGET = tp2.exe
SRC = $(wildcard $(SRC_FOLDER)*.cpp)
OBJ = $(patsubst $(SRC_FOLDER)%.cpp, $(OBJ_FOLDER)%.o, $(SRC))
EXE = $(BIN_FOLDER)/tp2.exe
ANALISAMEM = ./analisamem/bin/analisamem

all: build

mem: $(EXE)
	$(EXE) -i entrada.txt -o saida.txt -m 3 -s 1 -p /tmp/textlog.out -l

perf: $(EXE)
	$(EXE) -i $(ASSETS)200kText.txt -o $(OUT_FOLDER)200kOut.txt -m 3 -s 20 -p /tmp/200kText.out
	$(EXE) -i $(ASSETS)400kText.txt -o $(OUT_FOLDER)400kOut.txt -m 3 -s 20 -p /tmp/400kText.out
	$(EXE) -i $(ASSETS)600kText.txt -o $(OUT_FOLDER)600kOut.txt -m 3 -s 20 -p /tmp/600kText.out
	$(EXE) -i $(ASSETS)800kText.txt -o $(OUT_FOLDER)800kOut.txt -m 3 -s 20 -p /tmp/800kText.out
	$(EXE) -i $(ASSETS)1000kText.txt -o $(OUT_FOLDER)1000kOut.txt -m 3 -s 20 -p /tmp/1000kText.out
	$(EXE) -i $(ASSETS)1200kText.txt -o $(OUT_FOLDER)1200kOut.txt -m 3 -s 20 -p /tmp/1200kText.out
	$(EXE) -i $(ASSETS)1400kText.txt -o $(OUT_FOLDER)1400kOut.txt -m 3 -s 20 -p /tmp/1400kText.out
	$(EXE) -i $(ASSETS)1600kText.txt -o $(OUT_FOLDER)1600kOut.txt -m 3 -s 20 -p /tmp/1600kText.out
	$(EXE) -i $(ASSETS)1800kText.txt -o $(OUT_FOLDER)1800kOut.txt -m 3 -s 20 -p /tmp/1800kText.out
	$(EXE) -i $(ASSETS)2000kText.txt -o $(OUT_FOLDER)2000kOut.txt -m 3 -s 20 -p /tmp/2000kText.out

build: $(OBJ)
	$(CC) $(CXXFLAGS) -o $(BIN_FOLDER)$(TARGET) $(OBJ)

test: $(EXE)
	$(EXE) -i $(ASSETS)inputText.txt -o $(OUT_FOLDER)textOut.txt -m 3 -s 20 -p /tmp/inputText.out

$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

run: $(EXE)
	$(EXE) -I entrada.txt -O saida.txt -m 5 -s 10 -p /tmp/testlog.out

