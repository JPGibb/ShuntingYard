// ShuntingYard.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>

using namespace std;

//Creates a constant vlaue that cant be changed
const unsigned MAX_SIZE = 20;

//Function prototypes, declare what the functions take as input and what they return
void init(struct Stack*);
void init(struct Queue*);
void push(struct Stack*, char);
void push(struct Queue*, char);
char pop(struct Stack*);
char pop(struct Queue*);
bool isEmpty(struct Stack*);
bool isEmpty(struct Queue*);
bool isFull(struct Stack*);
bool isFull(struct Queue*);
bool isOperator(char);
bool should_pop(struct Stack*, char);

//Creates a structure called stack
struct Stack
{
	int top;
	char data[MAX_SIZE];
};

//Creates a structure called Queue
struct Queue
{
	int head;
	int tail;
	int count;
	char data[MAX_SIZE];
};

//main function is the entry point of the program
int main()
{
	cout << "Shunting Yard" << endl;

	struct Stack opStack;
	struct Queue outQueue;
	init(&opStack);
	init(&outQueue);

	cout << "Enter the infix notaition: ";
	string infix;
	getline(cin, infix);

	for (unsigned i = 0; i < infix.size(); ++i)
	{
		if (isdigit(infix[i]))
		{
			cout << "Is a number" << endl;
			push(&outQueue, infix[i]);
		}
		else if (isOperator(infix[i]))
		{
			cout << "Is operator" << endl;
			if (should_pop(&opStack, infix[i]))
			{
				push(&outQueue, pop(&opStack));
				push(&opStack, infix[i]);
			}
			else
			{
				push(&opStack, infix[i]);
			}

		}
		else if (infix[i] == '(')
		{
			cout << "Left paren" << endl;
			push(&opStack, infix[i]);

		}
		else if (infix[i] == ')')
		{
			cout << "Right paren" << endl;
			while (!isEmpty(&opStack))
			{
				if (opStack.data[opStack.top - 1] != '(')
				{
					push(&outQueue, pop(&opStack));
				}
				else
				{
					opStack.data[opStack.top - 1] = NULL;
					opStack.top--;
					cout << "top after paren: " << opStack.data[opStack.top] << endl;
					break;
				}
			}
		}
		else
		{
			cout << "Parse failure: Illegal character entered: " << infix[i] << endl;
			cin;
			return 0;
		}
	}


	while (!isEmpty(&opStack))
	{
		push(&outQueue, pop(&opStack));
	}
	while (!isEmpty(&outQueue))
	{
		cout << pop(&outQueue) << endl;
	}
}

//Will take stack as an input and initialise it
void init(struct Stack* s)
{
	s->top = 0;
}

//Will take queue as an input and initialise it
void init(struct Queue* q)
{
	q->head = NULL;
	q->tail = NULL;
	q->count = 0;
}

//Will add a new value to the top of the stack, and increment top
void push(struct Stack* s, char value)
{
	cout << "Pushing value: " << value << " to index: " << s->top << " of stack" << endl;
	s->data[s->top] = value;
	s->top++;
}

//Add a new value to the queue
void push(struct Queue* q, char value)
{
	cout << "Pushing value: " << value << " to index: " << q->tail << " of queue" << endl;
	q->data[q->tail] = value;
	q->tail++;
	q->count++;
}

//Returns the last item pput in the stack
char pop(struct Stack* s)
{
	cout << "Poping value index: " << s->top << " of stack" << endl;

	cout << "top index: " << s->top << endl;
	cout << "top value: " << s->data[s->top] << endl;

	char c = s->data[s->top - 1];
	s->top--;
	return c;
}

//Returns the item that has been in the queue the longest
char pop(struct Queue* q)
{
	cout << "Poping value index: " << q->head << " of queue ";
	//cout << q->head;
	char c = q->data[q->head];
	q->head++;
	q->count--;
	return c;
}

//Returns whether the stack is empty
bool isEmpty(struct Stack* s)
{
	if (s->top == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Returns wether the queue is empty
bool isEmpty(struct Queue* q)
{
	if (q->count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Returns wether the stack is full
bool isFull(struct Stack* s)
{
	if (s->top == MAX_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Returns wether the queue is full
bool isFull(struct Queue* q)
{
	if (q->head == MAX_SIZE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Returns wether the characters is an operator
bool isOperator(char c)
{
	if (c == '*' || c == '/' || c == '-' || c == '+')
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Returns whether the opStack should be popped or not
bool should_pop(struct Stack* opStack, char c)
{
	char top = opStack->data[opStack->top - 1];
	cout << top << endl;
	if (top == '(')
	{
		return 0;
	}
	if (top == c)
	{
		cout << "yes" << endl;
		return 1;
	}
	if (top == '*' || top == '/')
	{
		cout << "yes" << endl;
		return 1;
	}
	if (c == '+' && top == '+' || c == '-' && top == '+')
	{
		cout << "yes" << endl;
		return 1;
	}
	else
	{
		cout << "nope" << endl;
		return 0;
	}
}