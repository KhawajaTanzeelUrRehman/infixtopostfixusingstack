#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sstream>
#include <cmath>
using namespace std;

//class for the stack of string.
class stack {
	//class for the stack
public:
	int size;
	int top;
	string* arr;

	stack() {
		//Defualt constructor for the stack.
		size = 300;
		top = -1;
		arr = new string[size];
	}
	//args constructor for the stack.
	stack(int sizeofstack) {
		size = sizeofstack;
		top = -1;
		arr = new string[size];
	}

	bool isFull() {
		//function which check the stack is full or not.
		return top == size - 1;
	}

	bool isEmpty() {
		//funciton that check the function is empty.
		return top == -1;
	}

	void push(string value) {
		//funciton to push element in the stack
		if (isFull()) {
			cout << "This Stack is full." << endl;
		}
		else {
			top++;
			arr[top] = value;
		}
	}

	string pop() {
		//funciton to pop element from the stack.
		if (!isEmpty()) {
			return arr[top--];
		}
		else {
			return "!";
		}
	}

	void clear() {
		//function to deleter all entries
		top = -1;
	}

	string peak() {
		//funciton to pop element from the stack.
		if (!isEmpty()) {
			return arr[top];
		}
		else {
			return "!";
		}
	}
};
//Function to check the given input is valid or not.
int valid_check(string userinput) {
	//Creating object of the stack
	stack* obj = new stack();
	//using for loop on the string given by the user.
	for (int i = 0; i < userinput.length(); i++) {
		//condition that check for opening braces and storing it in the stack.
		if (userinput[i] == '(' || userinput[i] == '{' || userinput[i] == '[') {
			obj->push(string(1, userinput[i]));
		}
		//IF the stack is not empty then checking on closing braces 
		//for the open braces on the stack.. if found then pop that open braces.
		else if (!obj->isEmpty()) {
			string temp = obj->pop();
			//this condition will find the starting braces for the closing braces.
			if ((userinput[i] == ')' && temp == "(") || (userinput[i] == '}' && temp == "{")
				|| (userinput[i] == ']' && temp == "[")) {
			}
			//this condition will run if starting braces not found.
			else if (userinput[i] == ')' || userinput[i] == '}' || userinput[i] == ']') {
				return -1;
			}
			else {
				obj->push(temp);
			}
		}
		//This condition will run if the stack is empty and string start with closing braces.
		else if (userinput[i] == ')' || userinput[i] == '}' || userinput[i] == ']') {
			return -1;
		}
	}
	//if stack is empty. 
	if (obj->isEmpty()) {
		return 1;

	}
	else {
		//if the stack has some values.
		return -1;
	}
}
//function that check the priority of the character from the given string.
int priority(char a) {
	//Condition to check the given character is digit or not.
	if (a >= '0' and a <= '9') {
		return 1;
	}
	//Condition to check for brackets
	else if (a == '(' || a == ')' || a == '{' || a == '}' || a == '[' || a == ']') {
		return 2;
	}
	//Condition to check for + and -.
	else if (a == '+' || a == '-') {
		return 3;
	}
	//Condition to check for * and /.
	else if (a == '*' || a == '/') {
		return 4;
	}//Condition to check for power.
	else if (a == '^') {
		return 5;
	}
	else {
		return 0;
	}
}
//Fucntion that check for the validation and convert infix to postfix and evaluate it. 
void infixtopostfix() {
	//string variable to store input string , postfix to store the converted result, result is used to store digit of a number.
	string input, postfix, result;
	cout << "Enter the expression: ";
	cin >> input;
	//Stack to store operators.
	stack* stack1 = new stack();
	//valid_check function will return -1 if bracket count does not match.
	if (valid_check(input) == -1) {
		cout << "\nError in input expression. Brackets count does not match.\n" << endl;
	}
	//if brackets are valid
	else {
		//for loop to transverse on the given expression.
		for (int i = 0; i < input.length(); i++) {
			//Digit
			if (priority(input[i]) == 1) {
				postfix += input[i];
			}
			//Bracket 
			else if (priority(input[i]) == 2) {
				//adding space at the end of the last digit to seperate a number.
				if (postfix[postfix.length() - 1] != ' ' && isdigit(postfix[postfix.length() - 1])) {
					postfix += " ";
				}
				//pushing open brackets in the stack.
				if (input[i] == '(' || input[i] == '{' || input[i] == '[') {
					stack1->push(string(1, input[i]));
				}
				//for closing braket matching the paired open bracket and poping from the stack till finding the pair bracket.
				else if (input[i] == ')') {
					while (stack1->peak() != "(") {
						postfix += stack1->pop();
					}
					//for removing the open bracket from the stack.
					stack1->pop();

				}
				//for closing braket matching the paired open bracket and poping from the stack till finding the pair bracket.
				else if (input[i] == '}') {
					while (stack1->peak() != "{") {
						postfix += stack1->pop();
					}
					//for removing the open bracket from the stack.
					stack1->pop();
				}
				//for closing braket ']' matching the paired open bracket and poping from the stack till finding the pair bracket.
				else {
					while (stack1->peak() != "[") {
						postfix += stack1->pop();
					}
					//for removing the open bracket from the stack.
					stack1->pop();
				}
			}
			//+ - operator
			else if (priority(input[i]) == 3) {
				//adding space at the end of the last digit to seperate a number.
				if (postfix[postfix.length() - 1] != ' ' && isdigit(postfix[postfix.length() - 1])) {
					postfix += " ";
				}
				//removing all the operator of higher and equal precednece and adding to output string. 
				while (priority(stack1->peak()[0]) >= 3) {
					postfix += stack1->pop();
				}
				//adding the current operator in the stack.
				stack1->push(string(1, input[i]));
			}
			//* / operator
			else if (priority(input[i]) == 4) {
				//adding space at the end of the last digit to seperate a number.
				if (postfix[postfix.length() - 1] != ' ' && isdigit(postfix[postfix.length() - 1])) {
					postfix += " ";
				}
				//removing all the operator of higher and equal precednece and adding to output string.
				while (priority(stack1->peak()[0]) >= 4) {
					postfix += stack1->pop();
				}
				//adding the current operator in the stack.
				stack1->push(string(1, input[i]));
			}
			// Power "^" operator.
			else if (priority(input[i]) == 5) {
				//adding space at the end of the last digit to seperate a number.
				if (postfix[postfix.length() - 1] != ' ' && isdigit(postfix[postfix.length() - 1])) {
					postfix += " ";
				}
				//removing all the operator of higher and equal precednece and adding to output string.
				while (priority(stack1->peak()[0]) >= 5) {
					postfix += stack1->pop();
				}
				//adding the current operator in the stack
				stack1->push(string(1, input[i]));
			}
			else {
				continue;
			}

		}
		//adding space before removing all the operator to seperate the number.
		postfix += " ";
		//while loop to remove all operator from the stack.
		while (stack1->peak() != "!")
		{
			postfix += stack1->pop();
		}
		cout << "The Postfix Expression is: " << postfix << endl;
	}
	//clearing the stack to use it again in the evaluation part.
	stack1->clear();
	//for loop to transverse in the postfix expression.
	for (int i = 0; i < postfix.length(); i++) {
		//if the given index is a digit then storing it in a temp variable.
		if (priority(postfix[i]) == 1) {
			result += postfix[i];
		}
		//numbers are seperated by the spaces so if the given index is space then pushing the complete number in the stack.
		else if (postfix[i] == ' ') {
			//condition to check the variable has some number.
			if (result != "") {
				stack1->push(result);
			}
			result = "";
		}
		//if given index is number then poping the last two numbers from the stack and performing the respective function and pushing the result.
		else if (postfix[i] == '-') {
			double r = stod(stack1->pop());
			double l = stod(stack1->pop());
			stack1->push(to_string(l - r));
		}
		//if given index is number then poping the last two numbers from the stack and performing the respective function and pushing the result.
		else if (postfix[i] == '+') {
			double r = stod(stack1->pop());
			double l = stod(stack1->pop());
			stack1->push(to_string(l + r));

		}
		//if given index is number then poping the last two numbers from the stack and performing the respective function and pushing the result.
		else if (postfix[i] == '*') {
			double r = stod(stack1->pop());
			double l = stod(stack1->pop());
			stack1->push(to_string(l * r));
		}
		//if given index is number then poping the last two numbers from the stack and performing the respective function and pushing the result.
		else if (postfix[i] == '/') {
			double r = stod(stack1->pop());
			double l = stod(stack1->pop());
			stack1->push(to_string(l / r));
		}
		//if given index is number then poping the last two numbers from the stack and performing the respective function and pushing the result.
		else if (postfix[i] == '^') {
			double r = stod(stack1->pop());
			double l = stod(stack1->pop());
			stack1->push(to_string(pow(l, r)));

		}
		else {
			continue;
		}

	}
	//printing the evaluated result from the stack.
	cout << "The Calculated Result is :" << stod(stack1->pop()) << endl;

}
int main() {
	cout << "\nInfix to Postfix Converter\n\n" << endl;
	int i = -1;
	while (i != 0) {
		cout << "1-> To Enter Expression." << endl;
		cout << "0-> To Quit." << endl;
		cin >> i;
		if (i == 0) {
			break;
		}
		else if (i == 1) {
			infixtopostfix();
		}
		else {
			cout << "Invalid Entry: Please select from the given option";
		}
	}


	return 0;
}
