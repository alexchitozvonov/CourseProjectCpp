#pragma once
#include "Vector.h"
#include <array>
#include <vector>
#include <stack>
class Stack
{
private:
	stack<Vector> _elem;
	int _size;
	int _count;
public:
	Stack();
	Stack(int size);
	void Clear();
	void Push(Vector vector);
	Vector Pull();
	bool IsEmpty();
	int Size();
	~Stack();
};

