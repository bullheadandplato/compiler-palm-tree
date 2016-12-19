#ifndef _LEXAN_H_
#define _LEXAN_H_
#include"Base.h"
class LexAn : public Base
{
	private:
		FILE *fin;
		FILE *fout;
		char bufferin[2][256];
		char bufferscan[256];
	public:
		LexAn()
		{
			fin = fopen("in.txt", "r");
			fout = fopen("out.txt", "w");
		}
		virtual ~LexAn();
		void scanwords(); //Process each row
		void clearnotes();//Clear the comment and extra spaces
		void getwords(int state);//Process the word
		void wordkind(char str[]);//The word type is judged and output

        //getter and setters for the interface
        int getTotalCharacterCount();
        int getNumberOfIdentifiers();
        int getNumberOfKeywords();
        int getNumberOfComments();
        int getNumberOfOperators();
        int getNumberOfOtherSymbols();
};
#endif 
