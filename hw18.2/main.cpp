#include <iostream>
using namespace std;
class stack_size_error : public length_error {
public:
	explicit stack_size_error(const std::string& msg);
};
class stack_bad_alloc : public std::bad_alloc {
public:
	explicit stack_bad_alloc(void);
};
class stack_overflow : public std::logic_error {
public:
	explicit stack_overflow(const std::string& msg);
};
class stack_empty : public std::logic_error {
public:
	explicit stack_empty(const std::string& msg);
};

stack_size_error::stack_size_error(const std::string& msg) : std::length_error(msg) {};
stack_bad_alloc::stack_bad_alloc(void) : std::bad_alloc() {};
stack_overflow::stack_overflow(const std::string& msg) : std::logic_error(msg) {};
stack_empty::stack_empty(const std::string& msg) : std::logic_error(msg) {};

class Stack {
private:
	int* stackstore;
	int stacksize;
	int SP;
public:
	Stack(int size = 100);
	~Stack();
	void push(int value);
	int pop(void);
};

Stack::Stack(int size) {
	try {
		if (size == 0)
			throw stack_size_error("Розмір має бути додатним!");
	}
	catch (std::length_error le) {
		std::cout << "Розмір має бути додатним!" << std::endl;
	}

	try {
		stackstore = new int[size];
		if (size < 0)
			throw stack_bad_alloc();
	}
	catch (std::bad_alloc ba) {
		std::cout << "Bad alloc!" << std::endl;
	}
	stacksize = size;
	SP = 0;
}

Stack::~Stack(void) {
	delete[] stackstore;
}

void Stack::push(int value) {
	if (SP == stacksize)
		throw stack_overflow("Переповнення стоса!");
	stackstore[SP++] = value;
}

int Stack::pop(void) {
	try {
		if (SP == 0)
			throw stack_empty("Стос порожній!");
	}
	catch(std::logic_error ler){
		std::cout << "Stack is empty!" << std::endl;
	}
	
	return stackstore[--SP];
}

int main() {
	system("chcp 1251");

	std::cout << "\nStack overflow: " << std::endl;
	Stack stk;
	try {
		for (int i = 0; i < 100; i++) {
			stk.push(i);
		}
		stk.push(8);

	}
	catch (stack_overflow& exc)
	{
		cout << "Переповнення стека: елемент не доданий." << endl;
	}
	cout << stk.pop() << endl;

	std::cout << "\nStack size error: " << std::endl;
	Stack stk1(0);

	std::cout << "\nBad allocation: " << std::endl;
	Stack stk2(-5);

	std::cout << "\n Empty stack: " << std::endl;
	Stack stk3;
	stk3.pop();

	return 0;
}