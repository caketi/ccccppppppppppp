// Array.cpp : 定义控制台应用程序的入口点。
//


#include <iostream>

using namespace std;

class Array
{
public:
	Array(int length = 0);
	Array(const Array& arr);
	~Array();

	//重载赋值运算符
	const Array & operator = (const Array & arr);
	//重载 << 运算符
	friend ostream& operator << (ostream &out, const Array &arr);
	//重载 [] 运算符
	int &operator [](int index);

private:
	int m_length;
	int *m_ptrData;

};

Array::Array(int length):m_length(length)
{
	if (m_length == 0) m_ptrData = nullptr;
	else
		m_ptrData = new int[m_length];
}
Array::Array(const Array& arr)
{
	if (arr.m_length == 0) return;

	m_length = arr.m_length;
	m_ptrData = new int[m_length];
	//内存拷贝
	// memcpy(m_ptrData, arr.m_ptrData, sizeof(int) * m_length);
}
Array::~Array()
{
}
const Array& Array::operator = (const Array &arr)
{
	if (this == &arr) return *this;
	if (arr.m_length == 0) return *this;

	m_length = arr.m_length;
	m_ptrData = new int[m_length];
	//内存拷贝
	// memcpy(m_ptrData, arr.m_ptrData, sizeof(int) * m_length);
	return *this;
}
ostream& operator << (ostream &out, const Array &arr)
{
	for (int i = 0; i < arr.m_length; ++i)
	{
		out << arr.m_ptrData[i] << ",";
	}
	out << endl;
	return out;
}
int &Array::operator [](int index)
{
	if (index == 0) { }
	if (index < 0 || index >m_length)
	{
		//数组下标越界
	}

	return m_ptrData[index];
}
int main()
{
	Array arr(10);
	for (int i = 0; i < 10; i++)
	{
		arr[i] = i;
	}
	cout << arr;

	system("pause");
    return 0;
}
