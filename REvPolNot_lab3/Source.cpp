#include "ReversePolishNotation.h"
#include <iostream>

using namespace std;

int main()
{
	while (cin)
	{
		try
		{
			string expression;
			cout << ">";
			getline(cin, expression);
			Postfix test(expression);
			test.convert();
			cout << "Postfix: " << test.getPostfix() << endl;
			cout << "Result: " << test.calculate() << endl;
		}
		catch (...)
		{
			cout << "Wrong input\n";
		}
	}
}