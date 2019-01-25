#include "Stack.h"




Stack::Stack()
{
}
Stack::Stack(int size)
{
	_count = 0;
	if (size > 0)
	{
		_size = size;
		_elem = stack<Vector>();
	}
	else
	{
		throw new exception();
	}
}

void Stack::Clear()
{
	_size = 0;
	_count = 0;
	while (!_elem.empty())
	{
		_elem.pop();
	}
}

void Stack::Push(Vector vector)
{
	if (_count >= _size)
		throw new exception();
	_elem.push(vector);
	_count++;
}

Vector Stack::Pull()
{
	if (_count == 0)
		throw new exception();
	Vector temp = _elem.top();
	_elem.pop();
	return temp;
}

bool Stack::IsEmpty()
{
	return _elem.empty();
}

int Stack::Size()
{
	return _size;
}

Stack::~Stack()
{
}
