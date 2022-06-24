#include <iostream>
#include <string>
#include <fstream>
#include "Node.hpp"
#include "List.hpp"
#include "Vector.hpp"
#include "Dictionary.hpp"

std::string convertStringToLower(std::string word) {
    std::string aux;
    for (char c : word) {
        if (c!=',' && c!='.' && c!='!' && c!='?' && c!=':' && c!=';' && c!='_')
            aux += tolower(c);
    }
    return aux;
}

std::string runOrder(std::ifstream &inputFile, List* words) {
    std::string order;
    std::getline(inputFile, order);
    words->setLettersOrder(order);
    
    std::string aux;
    inputFile >> aux;
    return aux;
}

std::string runText(std::ifstream &inputFile, List* words) {
    std::string word;
    while(inputFile.good()) {
        inputFile >> word;

        if(word == "#ORDEM")
            return word;
        
        word = convertStringToLower(word);
        Dictionary * dictionary = words->search(word);
        if (dictionary->getWord() != "Not found!") {
            dictionary->increaseCount();
        } else {
            dictionary = new Dictionary(word);
            words->insertAtEnd(dictionary);
        }
    }
    return word;
}

int main(int argc, char const *argv[]) {
    std::ifstream inputFile("entrada.txt");
    std::ofstream outputFile("saida.txt");

    std::string aux;
    List* words = new List();

    if (inputFile.is_open() && outputFile.is_open()) {
        inputFile >> aux;
        for (int i = 0; i < 2; i++) {
            int option = 0;
            if(aux == "#ORDEM")
                option = 1;
            else if (aux == "#TEXTO")
                option = 2;

            std::getline(inputFile, aux); // ignores invalid line
            switch (option) {
                case 1:
                    aux = runOrder(inputFile, words);
                    break;
                
                case 2:
                    aux = runText(inputFile, words);
                    break;

                default:
                    std::cout << "Invalid option. ('#ORDEM' or '#TEXTO')" << std::endl;
            }
        }
    } else {
        std::cout << "Could not open the input or output file." << std::endl;
        return 0;
    }

    Vector *vector = words->passListToVector();
    delete words;
    vector->quickSort();
    vector->printOutFile(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
