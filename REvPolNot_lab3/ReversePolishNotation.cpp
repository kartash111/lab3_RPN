#include "ReversePolishNotation.h"
#include <stack>
#include <iostream>

bool notUnary(char symb)
{
	if (symb == '*' || symb == '/' || symb == '|' || symb == '(' || symb == ')') return true;
	return false;
}

bool isnumber(string numb)
{
	if (numb == "+" || numb == "-") return false;
	for (int i = 0; i < numb.length(); i++)
		if (!(numb[i] == '.' || numb[i] == '+' || numb[i] == '-' || isdigit(numb[i])))
			return false;
	return true;
}

//   Return values from priority function:
//
//			|	+	-	*	/	(	)
//		|	4	1	1	1	1	1	5
//		+	2	1	1	1	1	1	2
//		-	2	2	2	1	1	1	2
//		*	2	2	2	2	2	1	2	
//		/	2	2	2	2	2	1	2
//		(	5	1	1	1	1	1	3


int Postfix::priority(char stacksymb, char insymb)
{
	switch (insymb)
	{
	case('|'):
		switch (stacksymb)
		{
		case('|'):
			return 4;
		case('+'): case('-'): case('*'): case('/'):
			return 2;
		case('('): default:
			return 5;
		}
	case('+'): case('-'):
		switch (stacksymb)
		{
		case('|'): case('('):
			return 1;
		case('+'): case('-'):
			return 1;
		case('*'): case('/'):
			return 2;
		default:
			return 5;
		}
	case('*'): case('/'):
		switch (stacksymb)
		{
		case('|'): case('+'): case('-'): case('('):
			return 1;
		case('*'): case('/'):
			return 2;
		default:
			return 5;
		}
	case('('):
		return 1;
	case(')'):
		switch (stacksymb)
		{
		case('|'):
			return 5;
		case('+'): case('-'): case('*'): case('/'):
			return 2;
		case('('):
			return 3;
		default:
			return 5;
		}
	default:
		return 5;
	}
}
void unaryTransf(string& number) // --n -> n; ++n -> n
{
	bool minus = false;
	string newNumb = "";
	for (int i = 0; i < number.length(); i++)
	{
		if (number[i] == '-')
		{
			if (minus) minus = false;
			else minus = true;
		}
		if (isdigit(number[i]) || number[i] == '.') newNumb += number[i];
	}
	number = "";
	if (minus == true)
		number = '-' + newNumb;
	else number = newNumb;
}

void Postfix::parse(const string str, vector<string>& data)
{
	string number = "";
	for (int i = 0; i < str.length(); i++)
	{
		while (str[i] != ' ' && !notUnary(str[i]) && i != str.length() - 1) //reading a number
		{
			// if + or - isn't unary
			if ((str[i] == '+' || str[i] == '-') && (i > 0) && (isdigit(str[i - 1]))) break;
			number += str[i];
			i++;
		}

		if (!isnumber(number)) // the way, when in number is + or -
		{
			data.push_back(number);
			number = "";
		}

		if (number != "")
		{

			unaryTransf(number); // --n -> n; ++n -> n
			try {
				if (number != "") stod(number); // for --
			} // checking to the correct number
			catch (exception & e)
			{
				throw("Wrong input");
			}
			data.push_back(number);
			number = "";
		}

		if (str[i] == ' ')
		{
			continue;
			number = "";
		}
		else
		{
			string s(1, str[i]); // to convert char to string 
			data.push_back(s);
		}
	}
}

void Postfix::convert()
{
	vector<string> data;
	parse(infix, data);
	stack<char> tokens;
	tokens.push(END); // start symbol 
	for (int i = 1; i < data.size(); i++)
	{
		if (isnumber(data[i]))
			postfix += data[i];
		else
		{
			postfix += " ";
			int type = priority(tokens.top(), data[i][0]);
			switch (type)
			{
			case(1):	//	1 - put insymb to stack line
				tokens.push(data[i][0]);
				break;
			case(2):	//	2 - take symbol from stack and put it to postfix line
				postfix += tokens.top();
				tokens.pop();
				i--;
				continue;
			case(3):	//	3 - delete insymb and stacksymb
				tokens.pop();
				continue;
				break;
			case(4):	//	4 - succsessful end
				return;
			case(5): default:  //	5 - wrong input
				throw ("\nWrong input");
				break;
			}
		}
	}
}

double Postfix::calculate()
{
	vector<string> data;
	parse(postfix, data);
	stack<double> numbers;
	double number = 0;
	for (int i = 0; i < data.size(); i++)
	{
		if (isnumber(data[i]))
			numbers.push(stod(data[i]));
		else
		{
			double temp;
			if (numbers.empty()) throw("Wrong input");
			temp = numbers.top();
			numbers.pop();
			switch (data[i][0])
			{
			case('+'):
				temp = numbers.top() + temp;
				numbers.pop();
				break;
			case('-'):
				if (numbers.empty()) temp = -temp;
				else
				{
					temp = numbers.top() - temp;
					numbers.pop();
				}
				break;
			case('*'):
				temp = numbers.top() * temp;
				numbers.pop();
				break;
			case('/'):
				temp = numbers.top() / temp;
				numbers.pop();
				break;
			default:
				throw("Wrong input");
			}
			numbers.push(temp);
		}
	}
	if (numbers.size() > 1) throw("Wrong input");
	return numbers.top();
}