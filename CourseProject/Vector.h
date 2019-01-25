#pragma once
#include <cstdlib>
#include <list>
#include <vector>
using namespace std;

class Vector
{
private:
	vector<int> elems;
public:
	int GetThis(int i);
	void PushBack(int value);
	bool IsEmpty();
	void Clear();
	void PopBack();
	Vector();
	~Vector();
};

