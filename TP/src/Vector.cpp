#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "Vector.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

#define swap(X, Y) { std::string d = X; X = Y; Y = d; };

Vector::Vector() {
    this->size = 0;
}

Vector::Vector(int size) {
    erroAssert(size>0,"Null dimension");

    this->size = size;
    this->position = 0;
    this->items = (std::string*) malloc(this->size*sizeof(std::string));

    erroAssert(this->items!=NULL,"Malloc failed");
}

Vector::~Vector() {
    avisoAssert((this->size>0),"Vector has already been destroyed");
    this->size = -1;
}

int Vector::accessVector() {
    std::string aux;
    int s = 0;
    for (int i=0; i<this->size; i++){
        aux = this->items[i];
        s += aux.size();
    }
    return s; 
}

void Vector::writeElement(std::string word) {
    if (position != this->size) {
        this->items[this->position] = word;
        this->position += 1;
    } 
    else
        avisoAssert(1, "Vector is already full.");

    ESCREVEMEMLOG((long int)(&(this->items[this->position])), sizeof(std::string), 1);
}

std::string Vector::readElement (int pos) {
    erroAssert((pos>=0)&&(pos<this->size),"Invalid index");
    return this->items[pos];
}

void Vector::print() {
    for (int i = 0; i < this->size; i++) {
        std::cout << this->items[i] << " "; 
    } 
    std::cout << std::endl;
}

void Vector::printOrder() {
    for (int i = 0; i < MAXLETTERS; i++) {
        std::cout << this->lettersOrder[i] << " "; 
    } 
    std::cout << std::endl;
}

void Vector::printOutFile(std::ofstream &outputFile) {
    std::string previousWord = items[0];
    int count = 1;
    for (int i = 1; i < this->size; i++) {
        LEMEMLOG((long int)(&(this->items[i])), sizeof(std::string), 1);
        if (previousWord == items[i]) {
            count++;
        } else {
            outputFile << previousWord << " " << count;
            outputFile << std::endl;
            previousWord = items[i];
            count = 1;
        }
    }
    outputFile << previousWord << " " << count;
    outputFile << std::endl;
    outputFile << "#FIM";
    outputFile << std::endl;
}

void Vector::setLettersOrder(char lettersOrder[MAXLETTERS]) {
    for (int i = 0; i < MAXLETTERS; i++) {
        this->lettersOrder[i] = lettersOrder[i];
    }
}

int Vector::getCharValue(char c) {
    if((int)c < 65)
        return (int)c - 65;
    for (int i = 0; i < MAXLETTERS; i++) {
        if (c == this->lettersOrder[i])
            return i;
    }
    return (int)c;
} 

int Vector::biggerWord(std::string word1, std::string word2) {
    // this function returns 1 if the word1 must be first than word2
    // returns 2 if the word2 must be first than word1
    // return 0 if word1 and word2 are the same word 
    int wordSize1 = word1.size();
    int wordSize2 = word2.size();

    if (word1 == word2)
        return 0;

    for (int i = 0; i < wordSize1 && i < wordSize2; i++) {
        if (this->getCharValue(word1[i]) < this->getCharValue(word2[i]))
            return 1;
        if (this->getCharValue(word1[i]) > this->getCharValue(word2[i]))
            return 2;
    }

    if (wordSize1 < wordSize2)
        return 1;

    return 2;
}

void Vector::auxQuickSort(int left, int right) {
    int i = left;
    int j = right;

    if (right - left < this->arrayMinimumSize){
        insertionSort(left, right);
        return;
    }

    // choose pivot
    std::string pivot;
    if (medianArraySize == 1 || right - left < medianArraySize)
        pivot = this->items[(i + j) / 2];
    else {
        insertionSort(left, left + medianArraySize - 1);
        pivot = this->items[(left + (left + medianArraySize))/2];
    }
    while(i <= j) {
        while(this->biggerWord(pivot, this->items[i]) == 2 && i < right) {
            LEMEMLOG((long int)(&(this->items[i])), sizeof(std::string), 1);
            i++;
        }
        while(this->biggerWord(pivot, this->items[j]) == 1 && j > left) {
            LEMEMLOG((long int)(&(this->items[j])), sizeof(std::string), 1);
            j--;
        }
        if(i <= j) {
            ESCREVEMEMLOG((long int)(&(this->items[i])), sizeof(std::string), 1);
            ESCREVEMEMLOG((long int)(&(this->items[j])), sizeof(std::string), 1);
            swap(this->items[i], this->items[j]);
            i++;
            j--;
        }
    }
    
    if(j > left) 
        this->auxQuickSort(left, j);
    if(i < right) 
        this->auxQuickSort(i, right);
    
}

void Vector::quickSort(int medianArraySize, int arrayMinimumSize) {
    this->medianArraySize = medianArraySize;
    this->arrayMinimumSize = arrayMinimumSize;
    auxQuickSort(0, this->size-1);
}

void Vector::insertionSort(int left, int right) {
    int i, j;
    std::string aux;
    for (i = left+1; i <= right; i++) {
        aux = this->items[i];
        j = i - 1;
        while (j >= left && this->biggerWord(aux, this->items[j]) == 1) {
            LEMEMLOG((long int)(&(this->items[j])), sizeof(std::string), 1);
            ESCREVEMEMLOG((long int)(&(this->items[j+1])), sizeof(std::string), 1);
            this->items[j + 1] = this->items[j];
            j--;
        }
        this->items[j + 1] = aux;
    }
}