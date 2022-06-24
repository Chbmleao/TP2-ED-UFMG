#ifndef VECTORHPP
#define VECTORHPP

#include "Dictionary.hpp"

#define MAXLETTERS 26

class Vector {
	public:
		Vector();
		Vector(int size);
		~Vector();
		Dictionary* getItems();
		int accessVector();
		void writeElement(Dictionary item);
		Dictionary readElement(int pos);
		void print();
		void printOrder();
		void printOutFile(std::ofstream &outputFile);
		void setLettersOrder(char lettersOrder[MAXLETTERS]);
		int getCharValue(char c);
		int biggerDictionary(Dictionary dictionary1, Dictionary dictionary2);
		void quickSort();

	private:
		Dictionary * items;
		char lettersOrder[MAXLETTERS];
		int position;
		int size;
		void auxQuickSort(int left, int right);
};

#endif 