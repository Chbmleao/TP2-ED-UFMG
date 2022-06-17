#ifndef NODEHPP
#define NODEHPP

#include "Dictionary.hpp"

class Node {
    public:
        Node();
        Node(Dictionary* dictionary);
        ~Node();

    private:
        Dictionary *dictionary;
        Node *next;
    
    friend class List;
};

#endif