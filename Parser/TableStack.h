#ifndef _TABLESTACK_H_
#define _TABLESTACK_H_

#include"Parser.h"

class TableStack :public Parser
{
protected:
    vector<char> to_any;
    vector<char> left_any;
    int tableMap[100][100];
public:
    TableStack(){ memset(tableMap, -1, sizeof(tableMap)); }

	void get_table(); 
	void analyExp(string s); 
	void getAns(); 
    vector<char> getRightAny();
    vector<char> getLeftAny();
    int* getTableMap();
};
#endif
