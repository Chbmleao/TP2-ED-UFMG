#ifndef VECTORHPP
#define VECTORHPP

#define MAXLETTERS 26

class Vector {
	public:
		Vector();
		Vector(int size);
		~Vector();
		std::string* getItems();
		int getSize();
		int accessVector();
		void writeElement(std::string word);
		std::string readElement(int pos);
		void print();
		void printOrder();
		void printOutFile(std::ofstream &outputFile);
		void setLettersOrder(char lettersOrder[MAXLETTERS]);
		int getCharValue(char c);
		int biggerWord(std::string word1, std::string word2);
		void quickSort(int medianArraySize, int arrayMinimumSize);

	private:
		std::string *items;
		char lettersOrder[MAXLETTERS];
		int position;
		int size;
		void auxQuickSort(int left, int right);
		void insertionSort(int left, int right);
		int medianArraySize;
		int arrayMinimumSize;
};

#endif 