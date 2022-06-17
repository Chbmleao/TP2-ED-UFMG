#include "Node.hpp"

Node::Node() {
    this->dictionary = new Dictionary();
    this->next = nullptr;
}

Node::Node(Dictionary * dictionary) {
    this->dictionary = dictionary;
    this->next = nullptr;
}

Node::~Node() {}