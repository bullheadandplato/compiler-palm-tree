#ifndef _TABLESTACK_H_
#define _TABLESTACK_H_

#include"Google.h"

class TableStack :public Google
{
protected:
	vector<char> to_any; 
	vector<char> left_any;
	int tableMap[100][100];
public:
	TableStack(){ memset(tableMap, -1, sizeof(tableMap)); }

	void get_table(); 
	void analyExp(string s); 
	void print_out();
	void getAns(); 
};
#endif
