#include <iostream>
#include <string>
#include <fstream>
#include <getopt.h>
#include <string.h>
#include "Node.hpp"
#include "List.hpp"
#include "Vector.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

typedef struct opt{
    std::string logName;
    int regmem;
    std::string inputFile;
    std::string outputFile;
    int medianArraySize;
    int arrayMinimumSize;
} opt_tipo;

// print the use options
void use(){
    fprintf(stderr,"Main\n");
    fprintf(stderr,"\t-[i|I] entrada.txt \t(arquivo de entrada)\n");
    fprintf(stderr,"\t-[m|M] 1 \tmediana de M elementos para a escolha do pivo\n");
    fprintf(stderr,"\t-[s|S] 2 \ttamanho minimo das particoes\n");
    fprintf(stderr,"\t-p log.out\t(registro de desempenho)\n");
    fprintf(stderr,"\t-l \t\t(padrao de acesso e localidade)\n");
}

// read command line options and initialize variables
void parse_args(int argc,char ** argv, opt_tipo * opt){
    // external variables
    extern char * optarg;
    // auxiliar variable
    int c;

    // global variables inicialization
    opt->regmem = 0;
    opt->logName[0] = 0;
    opt->inputFile = "entrada.txt";
    opt->outputFile = "saida.txt";
    opt->medianArraySize = 1;
    opt->arrayMinimumSize = 2;
    
    // getopt - letter indicates option, : indicates parameter
    while ((c = getopt(argc, argv, "i:I:m:M:s:S:o:O:p:lh")) != EOF) {
        c = tolower(c);
        switch(c) {
            case 'i':
                opt->inputFile = std::string(optarg);
                break;
            case 'o':
                opt->outputFile = std::string(optarg);
                break;
            case 'm':
                opt->medianArraySize = atoi(optarg);
                break;
            case 's':
                opt->arrayMinimumSize = atoi(optarg);
                break;
            case 'p': 
                opt->logName = std::string(optarg);
                break;
            case 'l': 
                opt->regmem = 1;
                break;
            case 'h':
            default:
                use();
                exit(1);
        }
    }

    // verify the options consistency
    if (opt->inputFile.empty()) {
        opt->inputFile = "entrada.txt";
        avisoAssert(1, "Input File was not passed as parameter, 'entrada.txt' file will be used.");
    }  
    if (opt->outputFile.empty()) {
        opt->outputFile = "saida.txt";
        avisoAssert(1, "Output File was not passed as parameter, 'entrada.txt' file will be used.");
    }
    if (opt->medianArraySize < 1) {
        opt->medianArraySize = 1;
        avisoAssert(1, "Median Array Size was not passed as parameter, 1 value will be used.");
    }
    if (opt->arrayMinimumSize < 1) {
        avisoAssert(1, "Array Minimum Size was not passed as parameter, 1 value will be used.");
        opt->arrayMinimumSize = 1;
    }
    if (opt->logName.empty()) {
        opt->logName = "/tmp/tp2log.out";
        avisoAssert(1, "Log File Name was not passed as parameter, '/tmp/tp2log.out' value will be used.");
    }
}

std::string convertStringToLower(std::string word) {
    avisoAssert(!(word.empty()), "Empty string!");
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
        words->insertAtEnd(word);
    }
    return word;
}

int main(int argc, char **argv) {

    opt_tipo opt;
    // evaluate command line
    parse_args(argc, argv, &opt);

    // access log initialization
    
    char logName[opt.logName.size()];
    strcpy(logName, opt.logName.c_str());
    iniciaMemLog(logName);

    // activate or not the access log
    if (opt.regmem)
        ativaMemLog();
    else   
        desativaMemLog();

    std::ifstream inputFile(opt.inputFile);
    std::ofstream outputFile(opt.outputFile);

    std::string aux;
    List* wordsList = new List();

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
                    aux = runOrder(inputFile, wordsList);
                    break;
                
                case 2:
                    defineFaseMemLog(0);
                    aux = runText(inputFile, wordsList);
                    break;

                default:
                    erroAssert(option == 0, "Invalid option. File must contain '#ORDEM' and '#TEXTO'.");               
            }
        }
    } else {
        erroAssert(inputFile.is_open(), "Could not open the Input File.");
        erroAssert(outputFile.is_open(), "Could not open the output file.");
    }

    // pass the list elements to a vector, so we can use the quick sort algorithm 
    defineFaseMemLog(1);
    Vector *wordsVector = wordsList->passListToVector();
    delete wordsList;

    defineFaseMemLog(2);
    wordsVector->quickSort(opt.medianArraySize, opt.arrayMinimumSize);

    defineFaseMemLog(3);
    wordsVector->printOutFile(outputFile);

    finalizaMemLog();

    inputFile.close();
    outputFile.close();
    
    return 0;
}