#ifndef LISTHPP
#define LISTHPP

#define MAXLETTERS 26

#include "Node.hpp"
#include "Vector.hpp"

class List {
    public:
        List();
        ~List();
        int getSize();
        bool isEmpty();
        std::string getWord(int pos);
        void insertAtStart(std::string word);
        void insertAtEnd(std::string word);
        void insertAtPosition(std::string word, int pos);
        std::string removeAtStart();
        std::string removeAtEnd();
        std::string removeAtPosition(int pos);
        std::string search(std::string word);
        void setLettersOrder(std::string order);
        void print();
        void printOrder();
        void clean();
        Vector* passListToVector();

    private:
        int size;
        char lettersOrder[MAXLETTERS];
        Node* first;
        Node* last;
        Node* setPosition(int pos, bool before);
};

#endif