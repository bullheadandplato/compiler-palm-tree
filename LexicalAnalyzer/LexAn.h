#ifndef _LEXAN_H_
#define _LEXAN_H_
#include"Base.h"
#include<vector>
#include<string>
class LexAn : public Base
{
	private:
		FILE *fin;
		FILE *fout;
		char bufferin[2][256];
		char bufferscan[256];
        int totalCharCount=0;
        int commentCount=0;
        int identifierCount=0;
        int OperatorCount=0;
        int OtherSymbolCount=0;
        int keywordsCount=0;

        //the arrays for the data
        std::vector<std::string> identifiers;
        std::vector<std::string> keywords;
        std::vector<std::string> comments;
        std::vector<std::string> operators;
        std::vector<std::string> all;


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
        std::vector<std::string> getIdentifiers();
        std::vector<std::string> getKeywords();
        std::vector<std::string> getComments();
        std::vector<std::string> getOperators();
        std::vector<std::string> getAll();

};
#endif 
