#ifndef NODEHPP
#define NODEHPP

#include <string>

class Node {
    public:
        Node();
        Node(std::string word);
        ~Node();

    private:
        std::string word;
        Node *next;
    
    friend class List;
};

#endif