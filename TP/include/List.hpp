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
        Dictionary* getDictionary(int pos);
        void insertAtStart(Dictionary* dictionary);
        void insertAtEnd(Dictionary* dictionary);
        void insertAtPosition(Dictionary* dictionary, int pos);
        Dictionary* removeAtStart();
        Dictionary* removeAtEnd();
        Dictionary* removeAtPosition(int pos);
        Dictionary* search(std::string word);
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