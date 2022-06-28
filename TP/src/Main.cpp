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
    char logName[100];
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
                strcpy(opt->logName, optarg);
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
    if (opt->inputFile.empty()) 
        opt->inputFile = "entrada.txt";
    if (opt->outputFile.empty()) 
        opt->outputFile = "saida.txt";
    if (opt->medianArraySize < 1)
        opt->medianArraySize = 1;
    if (opt->arrayMinimumSize < 1)
        opt->arrayMinimumSize = 1;

    erroAssert(strlen(opt->logName)>0, "main - access log file name has to be set");
}

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
        words->insertAtEnd(word);
    }
    return word;
}

int main(int argc, char **argv) {

    opt_tipo opt;
    // evaluate command line
    parse_args(argc, argv, &opt);

    // access log initialization
    iniciaMemLog(opt.logName);

    // activate or not the access log
    if (opt.regmem)
        ativaMemLog();
    else   
        desativaMemLog();

    std::cout << opt.medianArraySize << " " << opt.arrayMinimumSize;

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
                    aux = runText(inputFile, wordsList);
                    break;

                default:
                    std::cout << "Invalid option. ('#ORDEM' or '#TEXTO')" << std::endl;
            }
        }
    } else {
        std::cout << "Could not open the input or output file." << std::endl;
        return 0;
    }

    Vector *wordsVector = wordsList->passListToVector();
    delete wordsList;
    
    wordsVector->quickSort(opt.medianArraySize, opt.arrayMinimumSize);
    wordsVector->printOutFile(outputFile);

    inputFile.close();
    outputFile.close();
    return 0;
}
