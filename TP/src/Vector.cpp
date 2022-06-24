#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include "Vector.hpp"
#include "msgassert.hpp"

#define swap(X, Y) { Dictionary d = X; X = Y; Y = d; };

Vector::Vector() {
    this->size = -1;
}

Vector::Vector(int size) {
    erroAssert(size>0,"Null dimension");

    this->size = size;
    this->position = 0;
    this->items = (Dictionary*) malloc(this->size*sizeof(Dictionary));

    erroAssert(this->items!=NULL,"Malloc failed");
}

Vector::~Vector() {
    avisoAssert((this->size>0),"Vector has already been destroyed");
    this->size = -1;
}

Dictionary * Vector::getItems() {
    return this->items;
}

int Vector::accessVector() {
    Dictionary aux = Dictionary();
    int s = 0;
    for (int i=0; i<this->size; i++){
        aux = this->items[i];
        s += aux.getCount();
    }
    return s; 
}

void Vector::writeElement(Dictionary item) {
    this->items[this->position] = item;

    this->position += 1;
}

Dictionary Vector::readElement (int pos) {
    erroAssert((pos>=0)&&(pos<this->size),"Invalid index");
    return this->items[pos];
}

void Vector::print() {
    for (int i = 0; i < this->size; i++) {
        this->items[i].print(); 
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
    for (int i = 0; i < this->size; i++) {
        outputFile << this->items[i].getWord() << " ";
        outputFile << this->items[i].getCount() << std::endl; 
    }
    outputFile << "#FIM";
}

void Vector::setLettersOrder(char lettersOrder[MAXLETTERS]) {
    for (int i = 0; i < MAXLETTERS; i++) {
        this->lettersOrder[i] = lettersOrder[i];
    }
}

int Vector::getCharValue(char c) {
    if((int)c < 65)
        return (int)c - 65;
    c = toupper(c);
    for (int i = 0; i < MAXLETTERS; i++) {
        if (c == this->lettersOrder[i])
            return i;
    }
    return (int)c;
} 

int Vector::biggerDictionary(Dictionary dictionary1, Dictionary dictionary2) {
    // this function returns 1 if the word1 must be first than word2, returns 2 otherwise 
    int wordSize1 = dictionary1.getWord().size();
    int wordSize2 = dictionary2.getWord().size();

    for (int i = 0; i < wordSize1 && i < wordSize2; i++) {
        if (this->getCharValue(dictionary1.getWord()[i]) < this->getCharValue(dictionary2.getWord()[i]))
            return 1;
        if (this->getCharValue(dictionary1.getWord()[i]) > this->getCharValue(dictionary2.getWord()[i]))
            return 2;
    }
    return 0;
}

void Vector::auxQuickSort(int left, int right) {
    int i, j;
    Dictionary pivot;
    i = left;
    j = right;
    pivot = this->items[(left + right) / 2];
     
    while(i <= j) {
        while(this->biggerDictionary(pivot, this->items[i]) == 2 && i < right) {
            i++;
        }
        while(this->biggerDictionary(pivot, this->items[j]) == 1 && j > left) {
            j--;
        }
        if(i <= j) {
            swap(this->items[i], this->items[j])
            i++;
            j--;
        }
    }
     
    if(j > left) {
        this->auxQuickSort(left, j);
    }
    if(i < right) {
        this->auxQuickSort(i, right);
    }
}

void Vector::quickSort() {
    auxQuickSort(0, this->size-1);
}