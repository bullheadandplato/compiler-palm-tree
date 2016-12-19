#ifndef _Base_H_
#define _Base_H_

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>


//C language keywords
static char keywords[50][13] = { "short", "int", "long", "float", "double", "char"
, "struct", "union", "enum", "typedef", "const", "unsigned", "signed", "extern"
, "static", "void", "if", "else", "switch", "case", "for", "do", "while",
"goto", "continue", "break", "default", "sizeof", "return", "true", "false" };

class Base
{
public:
	int buffernum;

public:
	Base(){ buffernum = 0; }
	virtual ~Base();

	int charkind(char c);	//Determines the character type
	int spaces(char c); //Whether the current space can be eliminated
	int characters(char c);//Whether it is a letter
	int keyword(char str[]);//Is a keyword
	int signwords(char str[]);// is an identifier
	int numbers(char c);//Whether it is a number
	int integers(char str[]);//Is an integer
	int floats(char str[]);//Whether it is floating-point type
};

#endif
