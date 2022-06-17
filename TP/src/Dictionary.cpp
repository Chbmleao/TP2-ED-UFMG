#include <string>
#include <iostream>
#include "Dictionary.hpp"

Dictionary::Dictionary() {
    this->count = 0;
    this->word = "";
}

Dictionary::Dictionary(std::string word) {
    this->count = 1;
    this->word = word;
}

std::string Dictionary::getWord() {
    return this->word;
}

int Dictionary::getCount() {
    return this->count;
}

void Dictionary::increaseCount() {
    this->count++;
}

void Dictionary::print() {
    std::cout << "("<< this->word << ":" << this->count << "), ";
}