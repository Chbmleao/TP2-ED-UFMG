#ifndef LISTHPP
#define LISTHPP

#define MAXLETTERS 26

#include "Node.hpp"

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
        int biggerDictionary(Dictionary dictionary1, Dictionary dictionary2);
        int getCharValue(char c);
        void print();
        void printOrder();
        void clean();

    private:
        int size;
        char lettersOrder[MAXLETTERS];
        Node* first;
        Node* last;
        Node* setPosition(int pos, bool before);
        void swap(Node* current, Node* previous, Node* previousPrevious);
};

#endif