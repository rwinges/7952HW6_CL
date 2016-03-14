//   3 * X + ( Y - 12 ) - Z
#include <iostream>
#include <stack>
#include <cctype>
#include <cstdlib>
using namespace std;

int getPrecedence(char character);
bool isArithmeticOperator(char symbol);

int main()
{
	const char CLOSE_PAREN = ')';
	const char OPEN_PAREN = '(';
	char symbol;
	string stringHolder;
	string postfixResult;

	cout << "\nInfix expression: ";

	//Initialize a stack of characters to hold the operation symbols and parentheses
	stack<char> operators;

	//DEBUG
	int i = 0;

	do
	{
		//DEBUG
		cout << endl
			 << "            i: " << i << endl
			 << "   cin.peek(): " << (char)cin.peek() << endl;

		// if the next input is a '('
		if (cin.peek() == OPEN_PAREN)
		{
			// Read the '(' and push in onto the stack
			symbol = (char)cin.get();
			operators.push(symbol);
			cin >> ws;
		}

		// if the next input is a number or other operand i.e. not an operator	
		else if (!isArithmeticOperator((char)cin.peek()) && cin.peek() != CLOSE_PAREN)
		{
			// Read the operand and write it to the output
			cin >> stringHolder;
			postfixResult += stringHolder;
			if (cin && cin.peek() != 13 && cin.peek() != 10)
			{
				cin >> ws;
			}

			//DEBUG
			cout << "postfixResult: " << postfixResult << endl;
		}

		// if the next input is an operator
		else if (isArithmeticOperator((char)cin.peek()))
		{
			//while:
			// (1) the stack is not empty
			// (2) the next symbol on the stack is not a '('
			// (3) the next symbol on the stack is not an operator with lower
			//     precedence than the next input symbol
			while (!operators.empty() &&
				   operators.top() != OPEN_PAREN &&
				   getPrecedence(operators.top()) >= getPrecedence((char) cin.peek()))
			{
				// Print the top operator and pop it
				postfixResult += operators.top();
				operators.pop();

				//DEBUG
				cout << "#postfixResult: " << postfixResult << endl;
			}

			// Read the next input symbol and push it onto the stack
			cin >> symbol;
			operators.push(symbol);
			cin >> ws;
		}

		else
		{
			//Read and discard the next input symbol (should be a ')')
			cin.ignore();
			cin >> ws;

			//Print the top operator and pop it; keep printing and popping until the next
			//symbol on the stack is a '('. If no '(' is encountered, then print an error
			//message indicating unbalanced parentheses and halt.
			do
			{
				postfixResult += operators.top();
				operators.pop();
			} while (operators.top() != OPEN_PAREN);

			//Finally, pop the '('.
			if (operators.top() == OPEN_PAREN)
			{
				operators.pop();
			} else
			{
				cout << "ERROR: Unbalanced parens." << endl;
			}
		}

		//DEBUG
		++i;
	} while (cin && cin.peek() != 13 && cin.peek() != 10); // while there is more of the expression left to read

	//Print and pop any remaining operations on the stack. (There should be no remaining left parentheses;
	//if there are, the input expression did not have balances parentheses.)
	while (!operators.empty())
	{
		if (operators.top() == OPEN_PAREN)
		{
			cout << "\nERROR: Unbalanced parenthesis." << endl;
		}
		else
		{
			postfixResult += operators.top();
			operators.pop();
		}
	}

	cout << "\nPostfix expression: " << postfixResult << endl;

	return EXIT_SUCCESS;
}

int getPrecedence(char character)
{
	switch (character)
	{
		case '+':	return 1;
		case '-':	return 1;
		case '*':	return 2;
		case '/':	return 2;
		default:	return 0;
	}
}

bool isArithmeticOperator(char symbol)
{
	switch (symbol)
	{
		case '+':	return true;
		case '-':	return true;
		case '*':	return true;
		case '/':	return true;
		default:	return false;
	}
}