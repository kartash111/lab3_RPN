#pragma once
#include <string>
#include <vector>

using namespace std;

const char END = '|';

class Postfix
{
public:
	Postfix() : infix(""), postfix("") {}
	Postfix(const string expr) : infix(END + expr + END), postfix("") {}  // infix = |expr|
	string getInfix() { return infix; }
	string getPostfix() { return postfix; }
	void convert(); // transformation infix to postfix
	double calculate(); //calculation of a expression value
private:
	string infix;
	string postfix;
	void parse(const string, vector<string>&); // first argument is string to parse and second where to parse
	int priority(char, char); // it return value, that says should symbol go: stack or postfix string
};