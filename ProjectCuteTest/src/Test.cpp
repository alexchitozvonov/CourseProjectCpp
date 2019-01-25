#include "../cute/cute.h"
#include "..\cute\ide_listener.h"
#include "..\cute\xml_listener.h"
#include "..\cute\cute_runner.h"
#include "..\..\CourseProject\Stack.h"
#include "..\..\CourseProject\Vector.h"
#include "..\..\CourseProject\Vector.cpp"
#include "..\..\CourseProject\Stack.cpp"


void VectorTestGetThis_positiveTest() {
	Vector vector = Vector();
	int expected1 = 2;
	int expected2 = 3;
	int expected3 = 4;
	int expected4 = 4;
	vector.PushBack(expected1);
	vector.PushBack(expected2);
	vector.PushBack(expected3);
	vector.PushBack(expected4);
	int testing1 = vector.GetThis(0);
	int testing2 = vector.GetThis(1);
	int testing4 = vector.GetThis(3);
	ASSERT(testing1 == expected1 && testing2 == expected2 && testing4 == expected4);
}
void VectorTestGetThis_negativeTest1() {
	Vector vector = Vector();
	ASSERT_THROWS(vector.GetThis(-1),exception);
}
void VectorTestGetThis_negativeTest2() {
	Vector vector = Vector();
	vector.PushBack(2);
	ASSERT_THROWS(vector.GetThis(1),exception);
}

void VectorTestPushBack() {
	Vector vector = Vector();
	int expect = 3;
	vector.PushBack(expect);
	ASSERT(vector.GetThis(0) == expect);
}

void VectorTestPopBack_positive() {
	Vector vector = Vector();
	vector.PushBack(3);
	vector.PopBack();
	ASSERT(vector.IsEmpty());
}

void VectorTestPopBack_negative() {
	Vector vector = Vector();
	ASSERT_THROWS(vector.PopBack(),exception);
}

void VectorTestIsEmpty() {
	Vector vector = Vector();
	ASSERT(vector.IsEmpty());
}

void VectorTestClear() {
	Vector vector = Vector();
	vector.PushBack(322);
	vector.Clear();
	ASSERT(vector.IsEmpty());
}

void VectorTestConstructor() {
	Vector vector = Vector();
	ASSERT(vector.IsEmpty());
}


//Stack


//FakeVector(mock)
//отсутсвует логическая реализация
//возвращает то что мы хотим
//будем подменять настоящий вектор
//там где это необходимо
class FakeVector
{
public:
	int GetThis(int arg,int willReturn)
	{
		return willReturn;
	}
};

void StackTestConstructor_postive() {
	Stack stack = Stack(3);
	ASSERT(stack.Size() == 3);
}

void StackTestConstructor_negative() {
	ASSERT_THROWS(Stack stack= Stack(-1),exception);
}

void StackClear() {
	Stack stack = Stack(1);
	Vector vector = Vector();
	stack.Push(vector);
	stack.Clear();
	ASSERT(stack.IsEmpty());
}

void StackPush_positive() {
	Stack stack = Stack(1);
	int expect = 322;
	Vector vector = Vector();
	vector.PushBack(expect);
	stack.Push(vector);
	//используем феиковый вектор вместо настоящего
	FakeVector fakeVector = FakeVector();
	ASSERT(fakeVector.GetThis(expect,expect) == stack.Pull().GetThis(0));
}

void StackPush_negative() {
	Stack stack = Stack(1);
	Vector vector = Vector();
	vector.PushBack(322);
	stack.Push(vector);
	ASSERT_THROWS(stack.Push(vector),exception);
}

void StackPull_negative() {
	Stack stack = Stack(1);
	ASSERT_THROWS(stack.Pull(),exception);
}

void StackPull_positive() {
	Stack stack = Stack(2);
	int expect1=322;
	int expect2=422;
	Vector vector1 = Vector();
	vector1.PushBack(expect1);
	Vector vector2 = Vector();
	vector2.PushBack(expect2);
	stack.Push(vector1);
	stack.Push(vector2);
	//используем феиковые векторы
	FakeVector fakeVector1 = FakeVector();
	FakeVector fakeVector2 = FakeVector();
	ASSERT(stack.Pull().GetThis(0) == fakeVector2.GetThis(expect2,expect2)
			&& stack.Pull().GetThis(0) == fakeVector1.GetThis(expect1,expect1) );
}

void StackIsEmpty() {
	Stack stack = Stack();
	stack.Push(Vector());
	stack.Clear();
	ASSERT(stack.IsEmpty());
}

void StackSize() {
	int size = 3;
	Stack stack = Stack(size);
	ASSERT(stack.Size() == size);
}
bool runAllTests(int argc, char const *argv[]) {
	cute::suite s { };

	//TODO add your test here
	s.push_back(CUTE(VectorTestGetThis_positiveTest));
	s.push_back(CUTE(VectorTestGetThis_negativeTest1));
	s.push_back(CUTE(VectorTestPopBack_negative));
	s.push_back(CUTE(VectorTestPopBack_positive));
	s.push_back(CUTE(VectorTestPushBack));
	s.push_back(CUTE(VectorTestGetThis_negativeTest2));
	s.push_back(CUTE(VectorTestIsEmpty));
	s.push_back(CUTE(VectorTestClear));
	s.push_back(CUTE(VectorTestConstructor));
	//Stack tests add
	s.push_back(CUTE(StackTestConstructor_postive));
	s.push_back(CUTE(StackTestConstructor_negative));
	s.push_back(CUTE(StackClear));
	s.push_back(CUTE(StackPush_positive));
	s.push_back(CUTE(StackPush_negative));
	s.push_back(CUTE(StackPull_negative));
	s.push_back(CUTE(StackPull_positive));
	s.push_back(CUTE(StackIsEmpty));
	s.push_back(CUTE(StackSize));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner = cute::makeRunner(lis, argc, argv);
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
