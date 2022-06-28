#include "Node.hpp"

Node::Node() {
    this->word = "";
    this->next = nullptr;
}

Node::Node(std::string word) {
    this->word = word;
    this->next = nullptr;
}

Node::~Node() {}