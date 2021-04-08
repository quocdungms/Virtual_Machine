#ifndef VM_H
#define VM_H

#include "main.h"


///////////////////////////////////////////////////////////
template <class T>
class Stack
{
	friend class VM;
public:
	class Node
	{
	public:
		T data;

		Node* next;
		//Node* prev;
	public:
		Node()
		{
			this->data = 0;
			this->next = NULL;
		}
		Node(T data)
		{
			this->data = data;
			this->next = NULL;
		}
	};
public:
	T pop();
	T getTop();
	T getData(int index);
	void push(T data);
	void push_back(T data);
	bool isEmpty();
	bool isFull();
	int size();
	void Clear();
	void print();
	void pr();
	Stack(int capacity);
	~Stack();

private:
	int count;
	int capacity;
	Node* top;
	Node* back;
};


template <class T>
T Stack<T>::getData(int index)
{
	Node* current = top;
	int pos = 0;
	while (current)
	{
		if (pos == index)
			return current->data;
		pos++;
		current = current->next;
	}
}
template <class T>
Stack<T>::Stack(int capacity)
{
	this->count = 0;
	this->capacity = capacity;
	this->top = NULL;
	this->back = NULL;
}
template <class T>
Stack<T>::~Stack()
{
	this->Clear();
}

template <class T>
void Stack<T>::Clear()
{
	Node* current = top;
	Node* next = current;
	while (current)
	{
		next = current->next;
		delete current;
		current = next;
	}
	count = 0;
	top = NULL;
	back = NULL;
}
template <class T>
bool Stack<T>::isEmpty()
{
	return this->top == NULL;
}

template <class T>
bool Stack<T>::isFull()
{
	return this->count == this->capacity;
}
template <class T>
int Stack<T>::size()
{
	if (top == NULL)
		return -1;
	return this->count;
}


template <class T>
void Stack<T>::pr()
{
	Node* p = top;
	if (!p)
		std::cout << "Stack is Empty\n";
	int t = 1;
	while (p)
	{
		std::cout << t << ". " << p->data << "\n";
		p = p->next;
		t++;
	}
}
template <class T>
void Stack<T>::print()
{
	if (this->isEmpty())
		throw "Stack is empty!\n";
	else
	{

		Node* p = top;
		printf("============ Stack ============\n");
		printf("*** Size = %d\n\n", this->count);
		printf("| Data | Next Address\n");
		while (p)
		{
			std::cout << "| " << p->data << " |";
			std::cout << " " << p->next << endl;
			p = p->next;
		}
		printf("\n");
		p = NULL;
		delete p;
	}
}

template <class T>
void Stack<T>::push(T data)
{
	if (this->isFull())
		throw StackFull(count);
	if (this->isEmpty())
	{
		Node* temp = new Node(data);
		temp->next = top;
		top = back = temp;
		count++;
	}
	Node* temp = new Node(data);
	temp->next = top;
	top = temp;
	count++;
}

template <class T>
void Stack<T>::push_back(T data)
{
	if (this->isFull())
		throw StackFull(count);
	if (this->isEmpty())
	{
		Node* temp = new Node(data);
		top = back = temp;
		count++;
		return;
	}
	Node* temp = new Node(data);
	back->next = temp;
	back = temp;
	count++;

}
template <class T>
T Stack<T>::pop()
{
	if (this->isEmpty())
		throw "Stack is Underflow!\n";
	Node* temp = top;
	T ans = temp->data;
	top = top->next;
	count--;
	delete temp;
	return ans;
}

template <class T>
T Stack<T>::getTop()
{
	if (top == NULL)
		throw "Stack is Empty!\n";
	return top->data;
}


////////////////////////////////////////////////////////////

struct REG
{
	int iData = 0;
	float fData = 0;
	bool bData = false;
	int address = 0;

	// None = -1
	// INT = 1
	// FLOAT = 2
	// BOOL = 3
	// ADDRESS = 4
	int type = -1;
};

class Command
{
	friend class VM;
public:
	string cmd;
	int dest;
	string src;

	Command()
	{
		this->cmd = "";
		this->dest = 0;
		this->src = "";


	}
	Command(string command, int dest, string src)
	{
		this->cmd = command;
		this->dest = dest;
		this->src = src;

	}
	//~Command();

};



class VM
{
public:

	// Suc chua cua day lenh
	int capacity;

	// So lenh da nhap vao 
	int size;

	// Dia chi cua lenh hien tai
	int IP;

	// 15 thanh ghi tinh
	REG reg[15];

	// stack luu day lenh chua xu ly
	Stack<string>* data_in;

	// Mang luu day lenh da xu ly
	Command command_list[65536];

	Stack<int> *state;


	VM()
	{
		this->capacity = 65536;
		this->size = 0;
		this->IP = 0; // 0A
		this->data_in = new Stack<string>(capacity);
		this->state = new Stack<int>(1000);
	}
	void run(string filename);

   /*
	* Cac ham check, get 
	*/

	bool check_int(string src);
	bool check_float(string src);
	bool check_bool(string src);
	bool check_address(string src);
	bool check_reg(string dest);
	int check_instruction(string command);
	bool valid_reg(int dest);

	int get_int(string src);
	float get_float(string src);
	bool get_bool(string src);
	int get_address(string src);
	int get_reg(string dest);
	int get_type(string src);
	int get_abs(int a);
	
   /*
    * Cac ham print
	*/

	void print_list();
	void print_reg();

	/*
	* Ham xu li
	*/


	//void load_data(string filename);
	void load_datav1(string filename);
	int classify(string command);
	void push_to_command_list(int address, string command, int dest, string src);
	void process();

	void ADD(int dest, string src, int address);
	void MINUS(int dest, string src, int address);
	void MUL(int dest, string src, int address);
	void DIV(int dest, string src, int address);


	void CMPEQ(int dest, string src, int address);
	void CMPNE(int dest, string src, int address);
	void CMPLT(int dest, string src, int address);
	void CMPLE(int dest, string src, int address);
	void CMPGT(int dest, string src, int address);
	void CMPGE(int dest, string src, int address);

	void NOT(int dest, int address);
	void AND(int dest, string src, int address);
	void OR(int dest, string src, int address);
	

	void MOVE(int dest, string src, int address);
	void LOAD(int dest, string src, int address);
	void STORE(int dest, string src, int address);


	int JUMP(string src, int address);
	int JUMPIF(int dest, string src, int address);
	int CALL(int IP, string src, int address);
	int RETURN();
	void HALT(int& address);

	void INPUT(int dest, int address);
	void OUTPUT(string src, int address);
	
	/*
	* Ham test, debug
	*/
	void test_regex(string filename);
	
};
#endif