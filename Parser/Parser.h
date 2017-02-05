#ifndef _Parser_H_
#define _Parser_H_
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cmath>
#include <stack>
using namespace std;

struct node
{
	char left;
	string right;
};

class Parser
{
protected:
	int T;
	node analy_str[100]; 
    std::vector<std::string> productions;
	set<char> first_set[100];
	set<char> follow_set[100];
	vector<char> ter_copy; 
	vector<char> ter_colt;
	vector<char> non_colt;

public:
    Parser() :T(0){}
	bool isNotSymbol(char c);
	int get_index(char target);
	int get_nindex(char target);
	void get_first(char target); 
	void get_follow(char target);
	void inputAndSolve(); 
	void display();
    void setT(int t);
    void setProductions(std::vector<string> product);

};
#endif 
