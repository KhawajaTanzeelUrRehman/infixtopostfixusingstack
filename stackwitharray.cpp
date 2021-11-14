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