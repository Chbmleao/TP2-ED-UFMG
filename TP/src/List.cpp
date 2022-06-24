#include <iostream>
#include "List.hpp"
#include "msgassert.hpp"

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

    erroAssert(pos <= this->size && pos >= 0, "Invalid Position!");

    p = this->first;
    for (i = 0; i < pos; i++) {
        p = p->next;
    }

    if(!before)
        p = p->next;

    return p;    
}

Dictionary* List::getDictionary(int pos) {
    Node *p;

    p = this->setPosition(pos);
    return p->dictionary;
}

// insert functions

void List::insertAtStart(Dictionary* dictionary) {
    Node *newNode;

    newNode = new Node();
    newNode->dictionary = dictionary;
    newNode->next = this->first->next;
    this->first->next = newNode;
    this->size++;

    if(newNode->next == NULL)
        this->last = newNode;
}

void List::insertAtEnd(Dictionary* dictionary) {
    Node *newNode = new Node();

    newNode->dictionary = dictionary;

    this->last->next = newNode;
    this->last = newNode;
    this->size++;
}

void List::insertAtPosition(Dictionary* dictionary, int pos) {
    Node *p, *newNode;

    p = this->setPosition(pos, true); // set position in current cell
    newNode = new Node();
    newNode->dictionary = dictionary;
    newNode->next = p->next;
    p->next = newNode;
    this->size++;

    if(newNode->next == NULL)
        this->last = newNode;
}

// remove functions

Dictionary* List::removeAtStart() {
    Dictionary* aux = new Dictionary();
    Node *p;

    erroAssert(!this->isEmpty(), "Empty list!");

    p = first->next;
    this->first->next = p->next;
    this->size--;
    if (this->first->next == NULL)
        this->last = this->first;
    aux = p->dictionary;
    delete p;

    return aux;
}

Dictionary* List::removeAtEnd() {
    Dictionary* aux;
    Node *p;

    erroAssert(!this->isEmpty(), "Empty list!");

    // set position p on the current node of last
    p = this->setPosition(this->size, true);

    p->next = NULL;
    this->size--;
    aux = this->last->dictionary;
    delete this->last;
    this->last = p;

    return aux;
}

Dictionary* List::removeAtPosition(int pos) {
    Dictionary *aux;
    Node *p, *q;

    erroAssert(!this->isEmpty(), "Empty list!");

    // set position p on the current node of pos
    p = this->setPosition(pos, true);
    q = p->next;
    p->next = q->next;
    this->size--;
    aux = q->dictionary;
    delete q;
    if (p->next == NULL) {
        this->last = p;
    }

    return aux;
}

Dictionary* List::search(std::string word) {
    Dictionary *aux = new Dictionary("Not found!");
    Node *p;

    if (this->isEmpty())
        return aux;

    p = this->first->next;

    while (p!=NULL) {
        if (p->dictionary->getWord() == word) {
            aux = p->dictionary;
            break;
        }
        p = p->next;
    }
    
    return aux;
}

void List::setLettersOrder(std::string order) {
    int i = 0;
    for(char& c : order) {
        c = toupper(c);
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
        p->dictionary->print();
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
    Vector *vector = new Vector(this->size);
    Node *currentNode = this->first->next;
    for (int i = 0; i < this->size; i++) {
        vector->writeElement(*(currentNode->dictionary));
        currentNode = currentNode->next;
    }
    vector->setLettersOrder(this->lettersOrder);
    return vector;
}