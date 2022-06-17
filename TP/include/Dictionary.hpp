#ifndef DICTIONARYHPP
#define DICTIONARYHPP

#include <string>

class Dictionary {
    public:
        Dictionary();
        Dictionary(std::string word);
        std::string getWord();
        int getCount();
        void increaseCount();
        void print();

    private:
        std::string word;
        int count;
};  

#endif