#include <iostream>
#include "List.hpp"
#include "msgassert.hpp"
#include "memlog.hpp"

List::List() {
    this->size = 0;
    this->first = new Node();
    this->last = this->first;
}

List::~List() {
    this->clean();
    delete this->first;
}

int List::getSize(){
    return this->size;
}

bool List::isEmpty(){
    return this->size == 0;
}

Node* List::setPosition(int pos, bool before=false) {
    Node *p; int i;

    erroAssert(pos < this->size && pos >= 0, "Invalid Position!");

    p = this->first;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }

    if(!before)
        p = p->next;

    return p;    
}

std::string List::getWord(int pos) {
    Node *p;

    p = this->setPosition(pos);
    return p->word;
}

// insert functions

void List::insertAtStart(std::string word) {
    Node *newNode;

    newNode = new Node();
    newNode->word = word;
    newNode->next = this->first->next;
    this->first->next = newNode;
    this->size++;

    if(newNode->next == NULL)
        this->last = newNode;
}

void List::insertAtEnd(std::string word) {
    Node *newNode = new Node();

    newNode->word = word;

    this->last->next = newNode;
    this->last = newNode;
    this->size++;

    ESCREVEMEMLOG((long int)(&(newNode->word)), sizeof(std::string), 0);
}

void List::insertAtPosition(std::string word, int pos) {
    Node *p, *newNode;

    p = this->setPosition(pos, true); // set position in current cell
    newNode = new Node();
    newNode->word = word;
    newNode->next = p->next;
    p->next = newNode;
    this->size++;

    if(newNode->next == NULL)
        this->last = newNode;
}

// remove functions

std::string List::removeAtStart() {
    std::string aux; 
    Node *p;

    erroAssert(!this->isEmpty(), "Empty list!");

    p = first->next;
    this->first->next = p->next;
    this->size--;
    if (this->first->next == NULL)
        this->last = this->first;
    aux = p->word;
    delete p;

    return aux;
}

std::string List::removeAtEnd() {
    std::string aux;
    Node *p;

    erroAssert(!this->isEmpty(), "Empty list!");

    // set position p on the current node of last
    p = this->setPosition(this->size, true);

    p->next = NULL;
    this->size--;
    aux = this->last->word;
    delete this->last;
    this->last = p;

    return aux;
}

std::string List::removeAtPosition(int pos) {
    std::string aux;
    Node *p, *q;

    erroAssert(!this->isEmpty(), "Empty list!");

    // set position p on the current node of pos
    p = this->setPosition(pos, true);
    q = p->next;
    p->next = q->next;
    this->size--;
    aux = q->word;
    delete q;
    if (p->next == NULL) {
        this->last = p;
    }

    return aux;
}

std::string List::search(std::string word) {
    std::string aux = "Not found!";
    Node *p;

    if (this->isEmpty())
        return aux;

    p = this->first->next;

    while (p!=NULL) {
        if (p->word == word) {
            aux = p->word;
            break;
        }
        p = p->next;
    }
    
    return aux;
}

void List::setLettersOrder(std::string order) {
    int i = 0;
    for(char& c : order) {
        c = tolower(c);
        if (c != ' ' && c != '\0') {
            this->lettersOrder[i] = c;
            i++;
        }
    }    
}

void List::print() {
    Node *p;

    p = this->first->next;
    while(p!=NULL) {
        std::cout << p->word << " ";
        p = p->next;
    }

    std::cout << std::endl;
}

void List::printOrder() {
    for (int i = 0; i < MAXLETTERS; i++) {
        std::cout << this->lettersOrder[i] << " ";
    }

    std::cout << std::endl;
}

void List::clean() {
    Node *p;

    p = this->first->next;
    while (p!=NULL) {
        this->first->next = p->next;
        delete p;
        p = this->first->next;
    }

    this->last = this->first;
    this->size = 0;
}

Vector* List::passListToVector() {
    Vector *vector = new Vector(this->size-1);
    Node *currentNode = this->first->next;
    for (int i = 0; i < this->size-1; i++) {
        LEMEMLOG((long int)(&(currentNode->word)), sizeof(std::string), 0);
        vector->writeElement(currentNode->word);
        currentNode = currentNode->next;
    }
    vector->setLettersOrder(this->lettersOrder);
    return vector;
}